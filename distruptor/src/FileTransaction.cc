#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <atomic>
#include <thread>



static int _my_write_sync(FILE *stream, char *buf, int size) {

	//1. write
	//2. fsync
	//3. dirent
	//4. fsync

	return 0;
}

static int _my_write_non_sync(FILE *stream, char *buf, int size) {
	return fwrite(buf, 1, size, stream);
}

FILE* my_open(const char *path, char *mode) {

	FILE *stream;

	if ((stream = fopen(path, mode)) == NULL) {
		perror("fail open\n");
	}

	return stream;

}

int my_write(FILE *stream, char *buf, int size, bool isSync) {

	if (isSync) {
		_my_write_sync(stream, buf, size);
	}
	else {
		_my_write_non_sync(stream, buf, size);
	}

	return 0;
}

int my_read(FILE *stream, char *buf, int size) {
	return fread(buf, 1, size, stream);
}

int my_close(FILE *stream) {

	return fclose(stream);
}


int test11() {



	return 0;
}