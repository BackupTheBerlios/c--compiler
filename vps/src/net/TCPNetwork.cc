#include "net/TCPNetwork.h"

TCPNetwork::TCPNetwork(short port)
{
	//open socket
	sockfd = socket(PF_INET,SOCK_STREAM,0);
	if(sockfd==-1) cout<<"[tcpnetwork]: create socket failed.\n";
	IPAddress server(port);
	//bind port
	if(bind(sockfd, (struct sockaddr*)&server,sizeof(struct sockaddr))==-1) cout<<"[tcpnetwork]: bind port failed.\n";

	//listen
	listen(sockfd, 128);
}

TCPNetwork::TCPNetwork()
{
	//open socket
	sockfd = socket(PF_INET,SOCK_STREAM,0);
	if(sockfd==-1) cout<<"[tcpnetwork]: create socket failed.\n";
}

// Client ruft request auf, Server ruft receive auf, Server antwortet mit reply
ssize_t TCPNetwork::request(const Server& server, void* req, size_t reqlen, void* res, size_t reslen, int timeout)
{
	//clear buffer !!!
	for(unsigned i=0;i<reslen;i++) *((char*)res+i)=0;

	//open socket
	clientfd = socket(PF_INET,SOCK_STREAM,0);
	
	while(connect(clientfd, (sockaddr*)&server, sizeof(sockaddr))==-1)
	{
		cout<<"[tcpnetwork] request(): connect failed.\n";
	}
		
// 	cout<<"[tcpnetwork] request(): eintritt.\n";
	// write
	ssize_t i=write(clientfd, req, reqlen);
// 	cout<<"[tcpnetwork] request(): nach write.\n";
	if (i==-1)
	{
		cout<<"[tcpnetwork] request(): write failed.\n";
		exit(-1);
	}
	// read
	ssize_t buffer=read(clientfd, res, reslen);
// 	cout<<"[tcpnetwork] request(): nach read.\n";
	if (buffer==-1)
	{
		cout<<"[tcpnetwork] request(): read failed.\n";
		exit(-1);
	}

	if(shutdown(clientfd, SHUT_RDWR)==-1)
	{
		cout<<"[tcpnetwork] request(): closing connection failed.\n";
	}
	close(clientfd);
	
// 	cout<<"[tcpnetwork] request(): success.\n";
	return buffer;
}

ssize_t TCPNetwork::receive(Client& client, void* req, size_t reqlen)
{
	
	// accept, blockiert solange bis eingehende Verbindung ankommt
	socklen_t slen = sizeof(sockaddr);
	
// 	cout<<"[tcpnetwork] receive(): eintritt.\n";
	
	lastfd = accept(sockfd, (sockaddr*)&client, &slen);
	if (lastfd==-1)
	{
		cout<<"[tcpnetwork] receive(): accept failed.\n";
		exit(-1);
	}
	
	//read
	ssize_t i = read(lastfd, req, reqlen);
	
	if (i==-1)
	{
		cout<<"[tcpnetwork] receive(): read failed.\n";
		exit(-1);
	}	
	
// 	cout<<"\n[tcpnetwork] receive(): success!.\n";
	return i;
}

ssize_t TCPNetwork::reply(const Client& client, void* res, size_t reslen)
{
	
// 	cout<<"\n[tcpnetwork] reply(): eintritt!.\n";
	//write
	ssize_t i = write(lastfd, res, reslen);
	
	if (i==-1)
	{
		cout<<"[tcpnetwork] reply(): write failed.\n";
		exit(-1);
	}
// 	cout<<"\n[tcpnetwork] reply(): success!.\n";
	close(lastfd);
	return i;
}
