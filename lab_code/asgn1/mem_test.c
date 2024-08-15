#include <stdio.h>
#include <fcntl.h> // For open()
#include <unistd.h> // For write(), close()
#include <string.h> // For memset()

#define DEVICE_FILE "/dev/asgn1"
#define BYTE_LENGTH 4096
#define BYTE_LENGTH2 4097

int main()
{
	int fd;
	ssize_t bytes_written;
	char buffer[BYTE_LENGTH];
	char buffer2[BYTE_LENGTH2];

	// Initialize buffer with 'A'
	memset(buffer, 'A', BYTE_LENGTH);
	memset(buffer2, 'A', BYTE_LENGTH2);

	// Open the device file
	fd = open(DEVICE_FILE, O_WRONLY);
	if (fd < 0) {
		perror("Failed to open the device file");
		return 1;
	}

	// Write fixed byte length to the device file
	bytes_written = write(fd, buffer, BYTE_LENGTH);
	if (bytes_written < 0) {
		perror("Failed to write to the device file");
		close(fd);
		return 1;
	}

	bytes_written = write(fd, buffer2, BYTE_LENGTH2);
	if (bytes_written < 0) {
		perror("Failed to write to the device file");
		close(fd);
		return 1;
	}
	// Close the device file
	close(fd);

	return 0;
}
