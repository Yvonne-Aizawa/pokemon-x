# Supported target

The initial target is one exact Pokémon X release. Do not mix files from different
regions or revisions; hashes are used to catch accidental mismatches.

Fill in the values below after running setup with the reference dump:

```text
Title ID: 0004000000055D00
Region: Not determined from the container metadata
Revision: Card revision 0; title version 0.0.0
ROM SHA-256: 62cc7268d594abdb36ffff77a868ba5f571b240afd985f5d5264843abb2e4c11
ExeFS SHA-256: 29eca9d82a8c3dc5c3ef335f8b164a4487dce7dc898932540081da874e7980f3
RomFS SHA-256: 7F2D061DDC420D143EE8C5CAE0EA18BF258354B33ABBE227AC40FD61B92013BD
```

The local container metadata reports product code `CTR-P-EKJA`, title ID
`0004000000055D00`, card revision `0`, and title version `0.0.0`. The title ID is
shared by multiple regional releases, so the region should be confirmed from the
dump's provenance before adding it here.

The project currently supports the target identified above only. Additional releases
should be added explicitly, with their own hashes and extraction notes.

