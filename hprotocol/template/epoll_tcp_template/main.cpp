#include <stdio.h>

#include <gtest/gtest.h>

#include "inc/epoll-server.h"
#include "inc/utils.h"


/**
 * 
 * TODO : 
 * 1. nonblocking 모드로 동작하므로 그에 따른 recv/send를 구현해야함
 * 2. peerstate 객체에 recv한 내용과 send한 내용을 알아야함
 * 3. server-client간의 통신중 처음에 몇개를 보낼지 알아야 nonblocking으로 구현가능
 * 4. 여기에 distruptor를 붙여서 TPS 측정
 * 5. serialize, deserialize를 구현하여 MQ 완성
 */

static int my_add(int a, int b) { return a + b; }

TEST(tdd_gtest, basic_gtest) { ASSERT_EQ(2, my_add(1, 1)); }

int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	run_server(argc, argv);

	return 0;
}