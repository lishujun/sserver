#include <winsock2.h>
#include <windows.h>
#include "datatype.h"
#include "global.h"

#pragma comment(lib, "ws2_32.lib")

SOCKET sockSrv;
SOCKADDR_IN addrSrv;
SOCKADDR_IN addrClient;


void network_cleanup()
{
	WSACleanup();
}

int network_initialize()
{
	

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 1, 1 );
	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		printf("WSAStartup ERROR!\n");
		return FALSE;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 || HIBYTE( wsaData.wVersion ) != 1 ) 
	{
		WSACleanup();
		printf("WSAStartup ERROR2!\n");
		return FALSE; 
	}

	sockSrv=socket(AF_INET,SOCK_STREAM,0);
	addrSrv.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(gs_config.port);
	
	if(sockSrv == -1)
	{
		return FALSE;
	}


	if(bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR))<0)
	{
		return FALSE;
	}

	if(listen(sockSrv,5)<0)
	{
		return FALSE;
	}


	return TRUE;
}

SOCKET apr_socket_accept()
{
	int len=sizeof(SOCKADDR);
	return accept(sockSrv,(SOCKADDR*)&addrClient,&len);
}

int apr_socket_recv(SOCKET sockConn,char *buf,int len)
{
	return recv(sockConn,buf,len,0);
}

int apr_socket_send(SOCKET sockConn,char *buf,int len)
{
	return send(sockConn,buf,len,0);//strlen(buf)+1,10
}

void apr_socket_close(SOCKET sockConn)
{
	closesocket(sockConn);
}

