#ifndef UDPNETWORK_H
#define UDPNETWORK_H

#include "net/IPNetwork.h"
#include <sys/time.h>
#include <iostream>
using namespace std;

/**
 * The UdpNetwork Class will be used to communicate through the network.
 *
 * every message to a server or to a client shall be send with the help of this class
 */
class UDPNetwork : IPNetwork {
public:
	/**
	 * Create a network object with a specified port. This is necessary for the server so that it can
	 * offer a service.
	 *
	 * @param port is the port that the server will be bound to
	 */
	UDPNetwork(short port);

	/**
	 * Create a network object. A client does not need to specify a port.
	 */
	UDPNetwork();

	/**
	 * Every time a client wants to communicate to the server it has to do a request. It sends its message
	 * with the command that shall be executed and waits for the answer of the server.
	 *
	 * @param server to whom the connection should be done
	 * @param req is the buffer that will be send through the network
	 * @param reqlen is the length of the buffer
	 * @param res is the buffer with the answer of the server
	 * @param reslen is the length of the buffer "res"
	 * @param timeout is the time (in seconds) that we wait for an answer
	 * @return the length of the received message
	 */
	ssize_t request(const Server& server, void* req, size_t reqlen, void* res, size_t reslen, int timeout=5);

	/**
	 * Wait the whole time for a message that arrives at a specified port.
	 *
	 * @param client is the information of the client that sent a request
	 * @param req is the buffer that will be send through the network
	 * @param reqlen is the length of the buffer
	 * @return the length of the received message
	 */
	ssize_t receive(Client& client, void* req, size_t reqlen);

	/**
	 * Send a message to the client from that we received a request.
	 *
	 * @param client is the information of the client that has been sent a request
	 * @param res is the buffer that will be send through the network
	 * @param reslen is the length of the buffer
	 * @return the length of the message that was sent
	 */
	ssize_t reply(const Client& client, void* res, size_t reslen);

	timeval to;
	
};

#endif
