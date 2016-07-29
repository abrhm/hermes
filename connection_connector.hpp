#pragma once

struct ConnectionConnector {
	ConnectionConnector (std::function<void(Message&)> sender, std::function<Message()> receiver)
	: send (sender)
	, receive (receiver)
	{
	}

	// Sender function
	std::function<void(Message&)> send;
	// Receiver function
	std::function<Message()> receive;
};