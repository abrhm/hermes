#include <algorithm>
#include <iostream>
#include <chrono>
#include <memory>
#include <vector>
#include <thread>
#include <string>

#include "connection.hpp"



template<int T>
class MockConnection : public ConnectionInterface {
public:
	MockConnection(ConnectionConnector connector)
	: ConnectionInterface (connector)
	{}

	virtual void loop () {
		std::cout << "MockConnection run " << T << std::endl;
		std::cout << "message: " << connector.receive() << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
};

/*
class ConnectionCollection {
public:

	ConnectionCollection () {std::cout << "ConnectionCollection constructor" << std::endl;};
	~ConnectionCollection () {
		std::cout << "ConnectionCollection destructor" << std::endl;
	};

	void add (Connection* c) {
		connections.push_back(std::unique_ptr<Connection>(c));
	}

	void run () {
		std::for_each(connections.begin(), connections.end(), [](std::unique_ptr<ConnectionInterface>& ci) { ci->run();});
	}

	void stop () {
		std::cout << "ConnectionCollection destroy" << std::endl;
		std::for_each(connections.begin(), connections.end(), [](std::unique_ptr<ConnectionInterface>& ci) { ci->stop();});
	}

private:
	std::vector<std::unique_ptr<Connection>> connections;
};
*/

int main() {
	Connection* c = new ConnectionImplementation<MockConnection<0>>();

	delete c;

	return 0;
}