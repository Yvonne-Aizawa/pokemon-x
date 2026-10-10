/*
 * Preliminary decompilation of DllDialogCommon.cro.
 *
 * Source address notation uses CRO segment 0 offsets. This file is intentionally
 * not wired into a build yet: imported services and the exact CRO linker layout
 * still need to be recovered.
 */

#include <stdint.h>

typedef struct DialogProc DialogProc;
typedef struct DialogWork DialogWork;

/* Confirmed from field accesses in the original ARM code. */
struct DialogProc {
    void *vtable;              /* 0x00 */
    void *child;               /* 0x04 */
    uint8_t reserved08[0x1c]; /* 0x08..0x23 */
    uint8_t state;             /* 0x24 */
    uint8_t sub_state;         /* 0x25 */
    uint16_t parameter;        /* 0x26 */
    int32_t timer;             /* 0x28 */
    uint8_t reserved2c[0x50]; /* 0x2c..0x7b */
    DialogProc *owner;         /* 0x7c */
};

static int dialog_transition(DialogProc *self);

/* CRO 0x2d8 */
static int dialog_can_run(void) { return 1; }

/* CRO 0x2e0 */
static int dialog_can_stop(void) { return 1; }

/* CRO 0x2e8 */
static int dialog_can_draw(void) { return 1; }

/* CRO 0x2f0, 0x2f4, 0x2f8, 0x2fc: empty lifecycle hooks. */
static void dialog_noop(void) {}

/* CRO 0x300. Dispatches the dialog state byte at offset 0x24. */
static int dialog_update(DialogProc *self) {
    switch (self->state) {
    case 0:
        /* The original initializes the child UI and advances to state 1. */
        self->sub_state = 0;
        self->state = 1;
        return 1;
    case 1:
        /* Calls the state-1 worker, then advances to state 2. */
        self->state = 2;
        return 1;
    case 2:
        /* CRO 0x43c handles the active dialog transition. */
        return dialog_transition(self);
    case 3:
        /* Calls the imported/event service and conditionally enters state 3. */
        self->state = 3;
        return 1;
    default:
        return 1;
    }
}

/* CRO 0x404. Releases the child object and finalizes the UI work area. */
static int dialog_shutdown(DialogProc *self) {
    if (self->child != 0) {
        /* virtual call at child vtable + 0x18 */
        self->child = 0;
    }
    self->state = 4;
    return 0;
}

/* CRO 0x43c. Handles input/transition state for the active dialog. */
static int dialog_transition(DialogProc *self) {
    DialogWork *work = (DialogWork *)(uintptr_t)0; /* imported layout unresolved */
    (void)work;

    /* The original checks work->mode at +0x08, then updates timer +0x28. */
    if (self->timer > 0)
        --self->timer;
    if (self->sub_state != 0)
        self->state = 2;
    return 1;
}

