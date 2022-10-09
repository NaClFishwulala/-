// echo_server.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include <winsock.h>
#pragma comment(lib,"wsock32.lib")
int main(int argc, char* argv[])
{
	SOCKET s,newsock;
	sockaddr_in ser_addr;
	sockaddr_in remote_addr;
	int len;
	int readLen = 0;
	int idx = 0;
	char buf[128];
	WSAData wsa;

	WSAStartup(0x101,&wsa);
	s = socket(AF_INET,SOCK_STREAM,0);
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	ser_addr.sin_port = htons(atoi(argv[1]));
	//ser_addr.sin_port = htons(0x1234);
	bind(s,(sockaddr*)&ser_addr,sizeof(ser_addr));

	listen(s,0);
	while(1){
		len = sizeof(remote_addr);
		newsock = accept(s,(sockaddr*)&remote_addr,&len);
		//while(readLen = recv(newsock, &buf[idx++], 1, 0))	//每次只读一字节
		//	send(newsock,"H",1,0);
		while(1)
		{
			recv(newsock, &buf[idx++], 1, 0);
			send(newsock,"H",1,0);
		}
		buf[idx] = '\0';
		printf("message: %s", buf);
		closesocket(newsock);
	}
	


	closesocket(s);
	WSACleanup();
	return 0;
}
