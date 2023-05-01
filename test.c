#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    FILE *fd = fopen("test.c", "r");

    if (fd < 0) {
        perror("open");
        return 1;
    }
    fseek(fd, 0L, SEEK_END);  // Move to the end of the file
    long int size = ftell(fd);  // Get the current position, which is the file size

    if (size == 0) {
        printf("The file is empty\n");
    } else {
        printf("The file size is %ld bytes\n", size);
    }


    return 0;
}