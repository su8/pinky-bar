man:
	-sed -e '15r ../README.md' 'man_template.pdc' | \
		sed -e '15,48d' | pandoc -s -S -f markdown -t man - -o pinkybar.1 

info: pinkybar.info

pinkybar.info:
	-sed -e '1,33d' '../README.md' | pandoc -s -S - -o pinkybar.texi
	$(MAKEINFO) --no-validate --no-warn --force pinkybar.texi
	-sed -i '2i @setfilename pinkybar.info' pinkybar.texi

.PHONY: man info pinkybar.info
