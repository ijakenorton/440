#include <stdio.h>
#include <stdbool.h>

#define BUF_SIZE 10
#define print_char(val) printf(#val " = %c\n", val)
#define print_int(val) printf(#val " = %d\n", val)

typedef struct {
	char *read;
	char *write;
	char buf[BUF_SIZE];
	int count; // Number of items in the buffer
} ringbuffer_t;

#define DECLARE_RINGBUFFER(name)   \
	ringbuffer_t name = {      \
		.read = name.buf,  \
		.write = name.buf, \
		.buf = { 0 },      \
		.count = 0,        \
	};

DECLARE_RINGBUFFER(ring_buffer);

// Choosing to believe that old data is more important than new data. If the count is equal to
// buffer size, the buffer is full and we will discard the incoming data
//

void ringbuffer_write(ringbuffer_t *ring_buffer, char value)
{
	if (ring_buffer->count == BUF_SIZE) {
		printf("Buffer is full, cannot write %c\n", value);
		return;
	}

	*ring_buffer->write = value;

	ring_buffer->write++;
	if (ring_buffer->write == ring_buffer->buf + BUF_SIZE) {
		ring_buffer->write = ring_buffer->buf;
	}

	ring_buffer->count++;
}

char ringbuffer_read(ringbuffer_t *ring_buffer)
{
	if (ring_buffer->count == 0) {
		printf("Buffer is empty, cannot read\n");
		return '\0';
	}

	char value = *ring_buffer->read;
	ring_buffer->read++;
	if (ring_buffer->read == ring_buffer->buf + BUF_SIZE) {
		ring_buffer->read = ring_buffer->buf;
	}

	ring_buffer->count--;
	return value;
}

void print_buffer(ringbuffer_t *ring_buffer)
{
	for (int i = 0; i < BUF_SIZE; ++i) {
		print_char(ringbuffer_read(ring_buffer));
	}
}

int main()
{
	for (char i = 'a'; i <= 'z'; i++) {
		ringbuffer_write(&ring_buffer, i);
	}

	print_int(ring_buffer.count);
	print_buffer(&ring_buffer);
	print_int(ring_buffer.count);

	for (char i = 'z'; i >= 'a'; i--) {
		ringbuffer_write(&ring_buffer, i);
	}

	print_buffer(&ring_buffer);
	print_int(ring_buffer.count);

	return 0;
}
