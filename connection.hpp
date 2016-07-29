#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <mutex>

#include "message.hpp"
#include "connection_connector.hpp"
#include "connection_interface.hpp"

class ConnectionConnector;

// TODO implementation must inherit from ConnectionInterface
template<typename Implementation>
class Connection {
public:
	Connection();
	~Connection() {};

	// Methods for core

	// Push messages from the core to the connection
	void push(std::vector<Message>&);
	// Fetch the outcoming messages to the core
	void fetch(std::vector<Message>&);

	// Methods for the ConnectionInterface
	static void send(Message&);

	static Message receive();

private:
	std::unique_ptr<ConnectionInterface> interface;
	// Propagete to the message handler
	std::vector<Message> messages_sending;
	// For users under this connection
	std::vector<Message> messages_received;
};

template<typename Implementation>
Connection<Implementation>::Connection ()
: interface (new Implementation(ConnectionConnector(send, receive)))
{
	std::cout << "constructor" << std::endl;
	messages_received.push_back("success");
}

template<typename Implementation>
void Connection<Implementation>::push (std::vector<Message>&)
{
/*	mtx.lock();
	std::move(income.begin(), income.end(), back_inserter(messages_received));
	income.erase(income.begin(), income.end());
	mtx.unlock();
	std::cout << "received size: " << messages_received.size() << std::endl;
*/
}

template<typename Implementation>
void Connection<Implementation>::fetch (std::vector<Message>&)
{
}

template<typename Implementation>
void Connection<Implementation>::send (Message&)
{
}

template<typename Implementation>
Message Connection<Implementation>::receive ()
{
	return Message("hello");
	// return messages_received.pop_back();
}
