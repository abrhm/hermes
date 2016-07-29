#pragma once
#include <iostream>
#include <thread>
#include <vector>

#include "message.hpp"
#include "connection_connector.hpp"

class ConnectionConnector;

class ConnectionInterface {
public:
	ConnectionInterface(ConnectionConnector);
	~ConnectionInterface();
	void run();
	void main();
	void stop();
	virtual void loop() = 0;
protected:
	bool running = false;

private:
	std::thread thread;
	ConnectionConnector connector;
};

// Implementation
ConnectionInterface::ConnectionInterface (ConnectionConnector conn)
: running (false)
, connector (conn)
{
	std::cout << "CONSTRUCTOR" << std::endl;
	std::cout << "message: " << connector.receive() << std::endl;
}

ConnectionInterface::~ConnectionInterface ()
{
	if (thread.joinable())
		thread.join();
}

void ConnectionInterface::run ()
{
	running = true;
	thread = std::thread([this] { this->main(); });
}

void ConnectionInterface::main ()
{
	while (running)
		loop();
}

void ConnectionInterface::stop ()
{
	running = false;
}