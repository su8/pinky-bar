\_pinkybar is zsh completion. This file will not be installed automatically.

pinkybar.1 is the generated man page from the pinkybar.pdc pandoc markdown source.

man page regeneration happens by installing the whole pandoc suite and invoking the following command:

```bash
pandoc -s -S -f markdown -t man pinkybar.pdc -o pinkybar.1
```
