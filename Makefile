PREFIX = ${HOME}/.local/
all:
	gcc rewrite.c -o rewrite
install_c: all
	cp -R ./rewrite ${DESTDIR}${PREFIX}/bin
	chmod 775 ${DESTDIR}${PREFIX}/bin/rewrite
install_py: all
	cp -R ./rewrite.py ${DESTDIR}${PREFIX}/bin/rewrite
	chmod 775 ${DESTDIR}${PREFIX}/bin/rewrite
clean :
	rm ./rewrite
