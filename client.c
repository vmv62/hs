#include <stdio.h>
#include <stdint.h>
#include "shm.h"
#include "client.h"

int main(int argc, char **argv){
	device_t *mem ;

	printf("%d\n", sizeof(device_t));
	mem = (device_t *)get_shmem(6767, sizeof(device_t));

	printf("%s\n", mem->volt.name);
	printf("%.2f\n", mem->volt.reg_value);

	return 0;
}
