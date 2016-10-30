To re-create the man page you'll have to install the whole pandoc suite and invoke the following commands:

```bash
make man
```

or

```bash
sed -e '15r ../README.md' 'man_template.pdc' | sed -e '15,48d' | pandoc -s -S -f markdown -t man - -o pinkybar.1
```

---

Open up Makefile and delete the PHONY line. Execute `touch man`, followed by `make man`.
