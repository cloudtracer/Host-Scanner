#include <iostream>
#include "stdafx.h"
#include "portscannerfactory.h"

using namespace std;

int main()
{
#if Windows
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cerr << "Failed to initialize WinSock." << endl;
		return EXIT_FAILURE;
	}
#endif

	// test TCP scanner

	{
		Services servs = {
			new Service("178.62.249.168", 21),
			new Service("178.62.249.168", 22),
			new Service("178.62.249.168", 25),
			new Service("178.62.249.168", 80),
			new Service("2a03:b0c0:2:d0::19:6001", 81),
			new Service("2a03:b0c0:2:d0::19:6001", 443),
			new Service("2a03:b0c0:2:d0::19:6001", 465),
			new Service("2a03:b0c0:2:d0::19:6001", 587)
		};

		auto scan = PortScannerFactory::Get(servs[0]->protocol);
		scan->Scan(&servs);
		scan->DumpResults(&servs);
		delete scan;
	}
	
	// test UDP scanner

	{
		Services servs = {
			new Service("178.62.249.168", 53, IPPROTO_UDP),
			new Service("208.67.222.222", 53, IPPROTO_UDP)
		};

		auto scan = PortScannerFactory::Get(servs[0]->protocol);
		scan->Scan(&servs);
		scan->DumpResults(&servs);
		delete scan;
	}

#if Windows
	WSACleanup();
	system("pause");
#endif

	return EXIT_SUCCESS;
}