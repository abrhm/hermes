#include <algorithm>
#include <iostream>
#include <chrono>
#include <memory>
#include <vector>
#include <thread>
#include <string>

class ConnectionInterface {
public:
	ConnectionInterface () {std::cout << "ConnectionInterface constructor" << std::endl;};
	virtual ~ConnectionInterface () {
		std::cout << "ConnectionInterface destructor" << std::endl;
		if (thread.joinable())
			thread.join();
	}
	virtual void main () {
		while (running) {
			loop();
		}
	};
	virtual void run () final {
		running = true;
		thread = std::thread([this] {this->main();});
	}

	void stop () {
		std::cout << "thread join" << std::endl;
		running = false;
	}

	virtual void loop() = 0;
protected:
	bool running = false;

private:
	std::thread thread;
};

template<int T>
class MockConnection : public ConnectionInterface {
public:
	MockConnection ()
	: ConnectionInterface()
	{
		std::cout << "MockConnection constructor " << T << std::endl;
	}

	virtual ~MockConnection () {
		std::cout << "MockConnection destructor " << T << std::endl;
	}

	virtual void loop () {
		std::cout << "MockConnection run " << T << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
};

class ConnectionCollection {
public:

	ConnectionCollection () {std::cout << "ConnectionCollection constructor" << std::endl;};
	~ConnectionCollection () {
		std::cout << "ConnectionCollection destructor" << std::endl;
	};

	void add (ConnectionInterface* ci) {
		connections.push_back(std::unique_ptr<ConnectionInterface>(ci));
	}

	void run () {
		std::for_each(connections.begin(), connections.end(), [](std::unique_ptr<ConnectionInterface>& ci) { ci->run();});
	}

	void stop () {
		std::cout << "ConnectionCollection destroy" << std::endl;
		std::for_each(connections.begin(), connections.end(), [](std::unique_ptr<ConnectionInterface>& ci) { ci->stop();});
	}

private:
	std::vector<std::unique_ptr<ConnectionInterface>> connections;
};

int main() {

	ConnectionCollection c;

	c.add(new MockConnection<0>());
	c.add(new MockConnection<1>());
	c.add(new MockConnection<2>());
	c.add(new MockConnection<3>());
	c.add(new MockConnection<4>());

	std::cout << "###########RUN" << std::endl;
	c.run();
	std::cout << "###########RUN" << std::endl;

	std::string a;

	std::cin >> a;
	c.stop();

	return 0;
}