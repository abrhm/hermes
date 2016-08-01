#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <mutex>

#include "message.hpp"
#include "connection_connector.hpp"
#include "connection_interface.hpp"

class ConnectionConnector;


class Connection {
public:
	Connection(ConnectionInterface* iface);
	~Connection () {};

	void push(std::vector<Message>&);
	void fetch(std::vector<Message>&);

	static void send(Message&);
	static Message receive();

private:
	std::unique_ptr<ConnectionInterface> interface;
	// Propagete to the message handler
	std::vector<Message> messages_sending;
	// For users under this connection
	std::vector<Message> messages_received;
};

Connection::Connection (ConnectionInterface* iface)
: interface(iface)
{
}

void Connection::push (std::vector<Message>&)
{
/*	mtx.lock();
	std::move(income.begin(), income.end(), back_inserter(messages_received));
	income.erase(income.begin(), income.end());
	mtx.unlock();
	std::cout << "received size: " << messages_received.size() << std::endl;
*/
}

void Connection::fetch (std::vector<Message>&)
{
}

void Connection::send (Message&)
{
}

Message Connection::receive ()
{
	return Message("hello");
	// return messages_received.pop_back();
}



template<typename Implementation>
class ConnectionImplementation : public Connection{
public:
	ConnectionImplementation();
	~ConnectionImplementation();
};

template<typename Implementation>
ConnectionImplementation<Implementation>::ConnectionImplementation ()
: Connection(new Implementation(ConnectionConnector(send, receive)))
{}