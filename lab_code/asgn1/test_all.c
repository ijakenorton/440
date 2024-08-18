#include <stdio.h>
#include <fcntl.h>    // For open()
#include <unistd.h>   // For write(), read(), close()
#include <string.h>   // For memset()
#include <errno.h>    // For errno, perror()

#define DEVICE_FILE "/dev/asgn1"
#define BYTE_LENGTH 4096
#define BYTE_LENGTH2 4097

int main()
{
    int fd;
    ssize_t bytes_written, bytes_read;
    char write_buffer[BYTE_LENGTH];
    char write_buffer2[BYTE_LENGTH2];
    char read_buffer[BYTE_LENGTH];
    
    // Initialize buffers with 'A' and 'B'
    memset(write_buffer, 'A', BYTE_LENGTH);
    memset(write_buffer2, 'B', BYTE_LENGTH2);
    memset(read_buffer, 0, BYTE_LENGTH);

    // Open the device file in write-only mode
    fd = open(DEVICE_FILE, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open the device file for writing");
        return 1;
    }

    // Write first buffer to the device file
    bytes_written = write(fd, write_buffer, BYTE_LENGTH);
    if (bytes_written < 0) {
        perror("Failed to write first buffer to the device file");
        close(fd);
        return 1;
    }

    // Write second buffer to the device file
    bytes_written = write(fd, write_buffer2, BYTE_LENGTH2);
    if (bytes_written < 0) {
        perror("Failed to write second buffer to the device file");
        close(fd);
        return 1;
    }

    // Close the device file after writing
    close(fd);

    // Open the device file in read-only mode
    fd = open(DEVICE_FILE, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open the device file for reading");
        return 1;
    }

    // Seek to the start of the file
    if (lseek(fd, 0, SEEK_SET) < 0) {
        perror("Failed to seek to the start of the file");
        close(fd);
        return 1;
    }

    // Read from the start of the file
    bytes_read = read(fd, read_buffer, BYTE_LENGTH);
    if (bytes_read < 0) {
        perror("Failed to read from the start of the file");
        close(fd);
        return 1;
    }

    printf("Read %zd bytes from the start of the file: %.*s\n", bytes_read, (int)bytes_read, read_buffer);

    // Seek to the middle of the file (at BYTE_LENGTH)
    if (lseek(fd, BYTE_LENGTH, SEEK_SET) < 0) {
        perror("Failed to seek to the middle of the file");
        close(fd);
        return 1;
    }

    // Read from the middle of the file
    memset(read_buffer, 0, BYTE_LENGTH);  // Clear the read buffer
    bytes_read = read(fd, read_buffer, BYTE_LENGTH);
    if (bytes_read < 0) {
        perror("Failed to read from the middle of the file");
        close(fd);
        return 1;
    }

    printf("Read %zd bytes from the middle of the file: %.*s\n", bytes_read, (int)bytes_read, read_buffer);

    // Seek to the end of the first buffer and start of the second buffer
    if (lseek(fd, BYTE_LENGTH2, SEEK_SET) < 0) {
        perror("Failed to seek to the end of the first buffer and start of the second buffer");
        close(fd);
        return 1;
    }

    // Read from this position
    memset(read_buffer, 0, BYTE_LENGTH);  // Clear the read buffer
    bytes_read = read(fd, read_buffer, BYTE_LENGTH);
    if (bytes_read < 0) {
        perror("Failed to read from the second buffer position in the file");
        close(fd);
        return 1;
    }

    printf("Read %zd bytes from the second buffer position in the file: %.*s\n", bytes_read, (int)bytes_read, read_buffer);

    // Close the device file after reading
    close(fd);

    return 0;
}

