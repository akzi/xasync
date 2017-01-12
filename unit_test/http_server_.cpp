#include "../../xhttp_server/include/xhttp_server.hpp"
#include "../include/xasync.hpp"

XTEST_SUITE(xhttp_server)
{

	void async_test(xhttp_server::request &req, xhttp_server::response &resp)
	{

	}


	XUNIT_TEST(async)
	{
		xhttp_server::xserver server;
		server.bind("127.0.0.1", 9001);
		server.regist(async_test);
		server.start();

		getchar();
	}
}