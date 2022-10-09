// hello_client.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <winsock.h>
#include <time.h>
#include <stdio.h>
#include "stdlib.h"
#pragma comment(lib,"wsock32.lib")

//记录时延数据的结构体
struct Time_Data
{
	clock_t start_t;
	clock_t end_t;
	double total_t;
}time_data;

int main(int argc, char* argv[])
{
	SOCKET s;
	sockaddr_in local,server;
	WSAData wsa;

	char recvbuf[128];

	//时间记录变量声明
	clock_t start_t, end_t;
	double total_t;

	int nums = 100;	//发送次数
	int idx = 0;
	int readLen = 0;


	WSAStartup(0x101,&wsa);

	s = socket(AF_INET,SOCK_STREAM,0);
	local.sin_family = AF_INET;
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local.sin_port = htons(0x3412);
	
	bind(s,(sockaddr*)&local,sizeof(local));

	server.sin_family = AF_INET;
	server.sin_addr.S_un.S_addr = htonl(INADDR_LOOPBACK);
	server.sin_port = htons(atoi(argv[1]));
	
	connect(s,(sockaddr*)&server,sizeof(server));
	
	start_t = clock();
	send(s, "h", 1, 0);
	nums--;
	//while(readLen =recv(s,&recvbuf[idx++], 1,0) && nums != 0)
	while(nums != 0)
	{
		send(s, "h", 1, 0);;//每次只收一个
		recv(s,&recvbuf[idx++], 1,0);
		nums--;
	}
    
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

	recvbuf[idx] = '\0';
	printf("CPU 占用的总时间：%f\n", total_t);
	printf("message: %s ", recvbuf);

	closesocket(s);
	WSACleanup();
	return 0;
}

