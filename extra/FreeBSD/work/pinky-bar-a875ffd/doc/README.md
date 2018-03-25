To re-create the man page and info document you'll have to install the whole pandoc suite, texinfo, gmake, gsed (replace sed in Makefile with gsed on \*BSD), then invoke:

```bash
make man info
```
