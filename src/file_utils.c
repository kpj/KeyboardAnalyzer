#include <stdio.h>
#include <unistd.h>

#include <ctype.h>
#include <string.h>

FILE *fd;

int openFile(char *path) {
	fd = fopen(path, "a+");
	return (fd == NULL) ? 0 : 1;
}

int closeFile() {
	return fclose(fd);
}

int appendFile(char *name, char *str) {
	openFile(name);
	int suc = -1;
	suc = fputs(str, fd);
	closeFile();
	return suc;
}
