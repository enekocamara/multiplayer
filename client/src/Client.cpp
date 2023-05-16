/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:02:42 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/16 16:34:06 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client(int port, std::string ipAddress)
{
	this->port = port;
	this->ipAddress = ipAddress;
	if ((pollfd.fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		throw std::runtime_error("failed to create socket");

	// Set up the server address structure
	address.sin_family = AF_INET;
	address.sin_port = htons(port); 
	if (inet_pton(AF_INET, ipAddress.c_str(), &address.sin_addr) <= 0)
		throw std::runtime_error("invalid address/ Address not supported");

	// Connect to the server
	if (connect(pollfd.fd, (sockaddr*)&address, sizeof(address)) == -1)
		throw std::runtime_error("failed to connect to server");

	int flags = fcntl(pollfd.fd, F_GETFL, 0);
	pollfd.events = POLLOUT | POLLIN;
	fcntl(pollfd.fd, F_SETFL, flags | O_NONBLOCK);
}

Client::~Client()
{
	
}

void	Client::start()
{
	//renderer.createWindow();
	
	//std::thread renderThread(&RenderEngine::render, &renderer);
	std::thread updateThread(&Client::updateData, this);
	renderer.render();
	updateThread.join();
}

void	Client::pollHandle()
{
	static bool		info = true;
	static Info	messageInfo = {};
	int events = poll(&pollfd, static_cast<nfds_t>(1), 1);
	if (events && pollfd.revents & POLLIN)
	{
		if (info)
			handleInfoMessage(info, messageInfo);
		else
			handleDataMessage(info, messageInfo);
	}
}

void	Client::handleInfoMessage(bool &info, Info &messageInfo)
{
	char buffer[sizeof(Info)];
	int received = recv(pollfd.fd, buffer, sizeof(buffer), 0);
	if (received == -1)
	{
		std::cerr << "error reciving the Info message\n";
		return ;
	}
	std::memcpy(&messageInfo, buffer, sizeof(Info));
	//std::cout << "message info flags " << (int)messageInfo.flags << " size " << (int)messageInfo.size << "\n";
	if (messageInfo.flags == FLAG_ID)
	{
		id = messageInfo.size;
		std::cout << "my id " << id << '\n';
	}
	else if (messageInfo.flags == FLAG_ENTITY_VECTOR)
	{
		info = false;
	}
	else if (messageInfo.flags == FLAG_PLAYER_VECTOR)
	{
		info = false;
	}
}

void	Client::handleDataMessage(bool &info, Info &messageInfo)
{
	if (messageInfo.flags == FLAG_PLAYER_VECTOR)
	{
		char *buffer =  new char[sizeof(Entity) * messageInfo.size];
		int		received = recv(pollfd.fd, buffer, sizeof(Entity) * messageInfo.size, 0);
		if (received <= 0)
		{
			info = true;
			return ;
		}
		posMutex.lock();
		data.updatePlayers(buffer, received);
		delete buffer;
		posMutex.unlock();
		info = true;
	}
	else if (messageInfo.flags == FLAG_ENTITY_VECTOR)
	{
		char *buffer =  new char[sizeof(Entity) * messageInfo.size];
		int		received = recv(pollfd.fd, buffer, sizeof(Entity) * messageInfo.size, 0);
		if (received <= 0)
		{
			info = true;
			return ;
		}
		posMutex.lock();
		data.updateEntities(buffer, received);
		delete buffer;
		posMutex.unlock();
		info = true;
	}
}

void	Client::updateData()
{
	while (1)
	{
		pollHandle();
	}
}

void	Client::sendNewPosition(glm::vec2 newPos)
{
	//std::cout << "sending position\n";
	Info messageInfo = {};
	messageInfo.flags = FLAG_NEW_POSITION;
	send(pollfd.fd, &messageInfo, sizeof(Info), 0);
	send(pollfd.fd, &newPos, sizeof(glm::vec2), 0);
}

void	Client::sendNewEntity(Entity newEntity)
{
	//std::cout << "sending position\n";
	Info messageInfo = {};
	messageInfo.flags = FLAG_NEW_ENTITY;
	send(pollfd.fd, &messageInfo, sizeof(Info), 0);
	send(pollfd.fd, &newEntity, sizeof(Entity), 0);
}