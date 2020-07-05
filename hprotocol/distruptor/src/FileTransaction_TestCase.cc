#include <gtest/gtest.h>

int my_write(FILE *stream, char *buf, int size, bool isSync);
int my_read(FILE *stream, char *buf, int size);
FILE* my_open(const char *path, char *mode);
int my_close(FILE *stream);

#define TESTCASE_NAME1 fileTransaction
#define TEST_FUNCTION  test11

#if 0

TEST(TESTCASE_NAME1, failWrite) {
	FILE *stream;

	stream = my_open("./fileTransaction.txt", "w+");

	const int write_size = 256;
	char write_buf[write_size] = "fileTransaction\n";
	my_write(stream, write_buf, write_size, false); 

	my_close(stream);
	stream = my_open("./fileTransaction.txt", "r+");

	const int size = 256;
	char buf[size] = { 0, };
	my_read(stream, buf, size);

	printf("%s\n", buf);
	my_close(stream);

	ASSERT_STRCASEEQ(write_buf, buf);

}

TEST(TESTCASE_NAME1, successWrite) {
	FILE *stream;

	stream = my_open("./fileTransaction2.txt", "w+");

	const int write_size = 256;
	char write_buf[write_size] = "fileTransaction2\n";
	my_write(stream, write_buf, write_size,  true);

	const int read_size = 256;
	char buf[read_size] = { 0, };
	my_read(stream, buf, read_size);

	printf("%s\n", buf);

	my_close(stream);

	ASSERT_STRCASEEQ(write_buf, buf);
}

TEST(TESTCASE_NAME1, fseekFile) {
	FILE *stream;

	stream = my_open("./fileTransaction3.txt", "w+");

	const int write_size = 256;
	char write_buf[write_size] = "fileTransaction3\n";
	my_write(stream, write_buf, write_size, false);

	
	fseek(stream, 0, SEEK_SET);

	const int size = 256;
	char buf[size] = { 0, };
	my_read(stream, buf, size);

	printf("%s\n", buf);
	my_close(stream);

	ASSERT_STRCASEEQ(write_buf, buf);

}

#endif