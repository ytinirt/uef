#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

#define PAGE_SIZE 4096

int main(int argc, char *argv[])
{
    int fd;
    void *map;
    int n;

    fd = open("/dev/rx_pool", O_RDWR);
    if (fd < 0) {
        printf("open failed\n");
        goto err_out;
    }

    map = mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        printf("mmap failed\n");
        goto err_out1;
    }

    for (n = 0; n < 10; n++) {
        printf("[%d] %s\n", n, (char *)map);
        sleep(5);
    }

    munmap(map, PAGE_SIZE);
    if (close(fd) != 0) {
        perror("close");
    }

    return 0;

err_out1:
    close(fd);
err_out:
    return -1;
}


