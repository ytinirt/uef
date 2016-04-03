#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

#define PAGE_SIZE 4096

int main(int argc, char *argv[])
{
    int fd;
    void *map;

    fd = open("/dev/rx_pool", O_RDWR);
    if (fd < 0) {
        printf("open failed\n");
        return -1;
    }

    map = mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        printf("mmap failed\n");
        goto err_out;
    }

    printf("%s\n", (char *)map);
    munmap(map, PAGE_SIZE);

    return 0;

err_out:
    munmap(map, PAGE_SIZE);
    return -1;
}


