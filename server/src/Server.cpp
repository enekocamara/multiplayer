/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:48:49 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/12 12:54:56 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include <fstream>
#include <string>

Server::Server()
{
	readConfig();
	config.address.sin_family = AF_INET;
	config.address.sin_addr.s_addr = INADDR_ANY;
	config.address.sin_port = htons( config.port );
	setSocket();
}

Server::~Server()
{
	
}

void	Server::handleSignals(int max)
{
	pollfdIt pIt = 1;
	int numOfEvents = 0;
	while(numOfEvents < max && pIt < data.size())
	{
		if (data[pIt].revents & POLLIN)
		{
			//std::cout << "signal received\n";
			char buffer[sizeof(glm::vec2)];
			int received = recv(data[pIt].fd, buffer, sizeof(buffer), 0);
			dataMutex.lock();
			glm::vec2 newPos;
			std::memcpy(&newPos, buffer, sizeof(glm::vec2));
			data[(posIt)pIt] = newPos;
			//std::memcpy(&data[(posIt)pIt], buffer, sizeof(glm::vec2));
			dataMutex.unlock();
			//std::cout << "unlocked\n";
			numOfEvents++;
		}
		pIt = pIt + 1;
	}
}

void printFPS() {
	static int frameCount = 0;
	static auto startTime = std::chrono::steady_clock::now();
	auto endTime = std::chrono::steady_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	
	if (elapsedTime >= 1000) {
		std::cout << "FPS: " << frameCount << std::endl;
		frameCount = 0;
		startTime = endTime;
	}
	frameCount++;
}


void	Server::run()
{
	listenConnection();
	while (1)
	{
		//printFPS();
		pollHandler();
		sendData();
		//std::cout << config.name << " is running\n";
		//std::cout << "port " << config.port << " is open\n";
	}
}

void	Server::pollHandler()
{
	int events;
	pollfdIt pIt = 0;
	events = poll(data.pollData(), static_cast<nfds_t>(data.size()), 1);
	if (data[pIt].revents & POLLIN)
		acceptConnection();
	handleSignals(events);
}

void	Server::sendData()
{
	Info messageInfo = {};
	for (pollfdIt i = 1; i < data.size(); i = i + 1)
	{
		dataMutex.lock();
		messageInfo.flags = FLAG_POS_VECTOR;
		messageInfo.size = data.size() - 1;
		std::cout << "message info flags " << (int)messageInfo.flags << " size " << (int)messageInfo.size << "\n";
		send(data[i].fd, &messageInfo, sizeof(Info), 0);
		send(data[i].fd, &data.posData()[1], sizeof(glm::vec2) * messageInfo.size, 0);
		dataMutex.unlock();
	}
}

void	Server::acceptConnection()
{
	unsigned int size = static_cast<unsigned int>(sizeof(config.address));
	struct pollfd new_client;
	pollfdIt pIt = 0;

	std::cout << "The connection has been accepted, continuing" << std::endl;
	dataMutex.lock();
	if ((new_client.fd = accept(data[pIt].fd, (struct sockaddr *)&config.address, &size)) == -1)
	{
		perror("connection refused");
		return;
	}
	Info info = {};
	info.flags = FLAG_ID;
	data.add(new_client.fd);
	info.size = static_cast<uint8_t>(data.size() - 2);
	std::cout << "message info flags " << (int)info.flags << " size " << (int)info.size << "\n";
	send(new_client.fd, &info, sizeof(Info), 0);
	dataMutex.unlock();
}

void	Server::readConfig()
{
	const char *pathConfig = "config/config.sv";

	std::ifstream file(pathConfig);
	
	if (!file.is_open())
		throw std::runtime_error("failed to open config file");

	std::string line;
	while (std::getline(file, line)) {
		config.update(line);
	}
	file.close();
}

void	Server::setSocket()
{
	int serverFd;

	if ((serverFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		throw std::runtime_error("failed to create socket");
	}
	data.add(serverFd);
	int flag = 1;
	int result = setsockopt(serverFd, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(int));
	if (result < 0)
	{
		throw std::runtime_error("failed to set TCP_NODELAY option");
	}
	if (bind(serverFd, (const struct sockaddr*)&config.address, sizeof(config.address)) == -1)
	{
		throw std::runtime_error("failed to bind socket");
	}
	int flags = fcntl(serverFd, F_GETFL, 0);
	fcntl(serverFd, F_SETFL, flags | O_NONBLOCK);
}

void	Server::listenConnection()
{
	std::cout << "Server started, im listening" << std::endl;
	if (listen(data[(pollfdIt)0].fd, 3) == -1)
	{
		perror("listening process failure");
		exit(EXIT_FAILURE);
	}
}