#include "stdio.h"
#include "string.h"

int  main(int argc, char **argv){
	FILE *fd;

	fd = fopen(CONF_FILE, "r");

	fclose(fd);
}
