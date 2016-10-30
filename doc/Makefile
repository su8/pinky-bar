man:
	-sed -e '15r ../README.md' 'man_template.pdc' | \
		sed -e '15,48d' | pandoc -s -S -f markdown -t man - -o pinkybar.1 

.PHONY: man
