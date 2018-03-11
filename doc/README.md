To re-create the man page and info document you'll have to install the whole pandoc suite, texinfo, gmake, gsed (replace sed with gsed on \*BSD), then invoke:

```bash
make man info
```

---

Open up Makefile and delete the PHONY line. Execute `touch man`, followed by `make man`, bring back the PHONY line and execute `make man`.
