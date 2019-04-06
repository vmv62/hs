#define SHM_KEY 5476
#define SHMSZ 1500

int *set_shmem(int key, int size);
int *get_shmem(int key, int size);
