#include <stdio.h>
#include <stdint.h>
#include "shm.h"
#include "client.h"

int main(int argc, char **argv){
	device *dev ;

	dev = (device *)get_shmem(6767, sizeof(device));

	printf("%s", dev[0]->name);

	return 0;
}
