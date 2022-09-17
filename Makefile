all:
	gcc rewrite.c -o rewrite
install: all
	cp -R wordlist-rewriter/rewrite ${DESTDIR}${PREFIX}/bin
	chmod 775 ${DESTDIR}${PREFIX}/bin/rewrite
