#include "net/UDPNetwork.h"

UDPNetwork::UDPNetwork(short port)
{
	//open socket
	sockfd = socket(PF_INET,SOCK_DGRAM,0);
 	IPAddress server(port);
	//bind port
 	bind(sockfd, (struct sockaddr*)&server,sizeof(struct sockaddr));	
}

UDPNetwork::UDPNetwork()
{
	//open socket
	sockfd = socket(PF_INET,SOCK_DGRAM,0);
}

// Server ruft receive auf, Client soll request aufrufen, Server antwortet mit reply
ssize_t UDPNetwork::request(const Server& server, void* req, size_t reqlen, void* res, size_t reslen, int timeout)
{
	//clear buffer !!!
	for(unsigned i=0;i<reslen;i++) *((char*)res+i)=0;

	while(1)
	{
		//send
		if (sendto(sockfd, req, reqlen, 0, (sockaddr*)&server, sizeof(sockaddr))==-1)
		{
			cout<<"[udpnetwork] request(): sendto failed.\n";
			exit(-1);
		}
		to.tv_sec = timeout;
		to.tv_usec = 0;
		fd_set fds;	
		FD_ZERO(&fds);
		FD_SET(sockfd, &fds);
		int ret = select(sockfd+1, &fds, NULL, NULL, &to);
		if (ret) return recv(sockfd, res, reslen, 0);
		
		// timeout...
		cout<<"[udpnetwork] timeout in request()\n";
	}

	return 0;
}

ssize_t UDPNetwork::receive(Client& client, void* req, size_t reqlen){
	//recvfrom, blocks until a message arrives
	socklen_t slen = sizeof(sockaddr);
	ssize_t i = recvfrom(sockfd, req, reqlen, 0, (sockaddr*)&client, &slen);
	if (i==-1)
	{
		cout<<"[udpnetwork] receive(): recvfrom failed.\n";
		exit(-1);
	}
		
	return i;
}

ssize_t UDPNetwork::reply(const Client& client, void* res, size_t reslen){
	//sendto
	ssize_t i = sendto(sockfd, res, reslen, 0, (sockaddr*)&client, sizeof(sockaddr));
	if (i==-1)
	{
		cout<<"[udpnetwork] reply(): sendto failed.\n";
		exit(-1);
	}
	return i;
}




 
