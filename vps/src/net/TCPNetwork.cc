#include "net/TCPNetwork.h"

TCPNetwork::TCPNetwork(short port)
{
	//open socket
	sockfd = socket(PF_INET,SOCK_SEQPACKET,0);
	IPAddress server(port);
	//bind port
	bind(sockfd, (struct sockaddr*)&server,sizeof(struct sockaddr));	
	
	//listen
	listen(sockfd, 128);
}

TCPNetwork::TCPNetwork()
{
	//open socket
	sockfd = socket(PF_INET,SOCK_DGRAM,0);
}

// Server ruft receive auf, Client soll request aufrufen, Server antwortet mit reply
ssize_t TCPNetwork::request(const Server& server, void* req, size_t reqlen, void* res, size_t reslen, int timeout)
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
		socklen_t slen = sizeof(sockaddr);
		
		// todo: sequenznummer einfuegen und pruefen, ob diese mit response uebereinstimmt
		if (ret) return recvfrom(sockfd, res, reslen, 0, (sockaddr*)&server, &slen);
		
		// timeout...
		cout<<"[udpnetwork] timeout in request()\n";
	}

	return 0;
}

ssize_t TCPNetwork::receive(Client& client, void* req, size_t reqlen){
	
	// accept, blockiert solange bis eingehende Verbindung ankommt
	socklen_t slen = sizeof(sockaddr);
	
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
		
	return i;
}

ssize_t TCPNetwork::reply(const Client& client, void* res, size_t reslen){
	
	//write
	ssize_t i = write(lastfd, res, reslen);
	
	if (i==-1)
	{
		cout<<"[tcpnetwork] reply(): write failed.\n";
		exit(-1);
	}
	return i;
}




 
