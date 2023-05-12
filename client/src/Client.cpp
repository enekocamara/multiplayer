/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:02:42 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/12 15:56:57 by ecamara          ###   ########.fr       */
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
		{
			char buffer[sizeof(Info)];
			int received = recv(pollfd.fd, buffer, sizeof(buffer), 0);
			if (received == -1)
			{
				std::cerr << "error reciving the message\n";
				return ;
			}
			std::memcpy(&messageInfo, buffer, sizeof(Info));
			//std::cout << "message info flags " << (int)messageInfo.flags << " size " << (int)messageInfo.size << "\n";
			if (messageInfo.flags == FLAG_ID)
			{
				id = messageInfo.size;
				std::cout << "my id " << id << '\n';
			}
			else
			{
				info = false;
			}
		}
		else
		{
			char *buffer =  new char[sizeof(Entity) * messageInfo.size];
			//std::cout << "message size [" << (int)messageInfo.size << "]\n";
			int		received = recv(pollfd.fd, buffer, sizeof(Entity) * messageInfo.size, 0);
			if (received <= 0)
			{
				//std::cerr << "error receiving glm::pos\n";
				info = true;
				//exit(0);
				return ;
			}
			//std::cout << '[' << buffer << ']' << received << '\n';
			posMutex.lock();
			data.update(buffer, received);
			delete buffer;
			posMutex.unlock();
			//std::cout << "vec3 = " << data[0].x << ',' << data[0].y << '\n';
			info = true;
			//size = 0;
		}
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
	send(pollfd.fd, &newPos, sizeof(glm::vec2), 0);
}