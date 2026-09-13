all:
	clang -o file-utils file-utils.c helpers.c command-code/cp-it.c command-code/find-content.c command-code/find-name.c