/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:48:49 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/17 12:58:42 by ecamara          ###   ########.fr       */
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
	pollfdIt		pIt = 1;
	static bool		info = true;
	int numOfEvents	= 0;
	static Info	messageInfo = {};

	while(numOfEvents < max && pIt < data.playerSize())
	{
		
		if (data[pIt].revents & POLLIN)
		{
			if (info)
			{
				handleInfoMessage(pIt, info, messageInfo);
			}
			else
			{
				handleDataMessage(pIt, info, messageInfo);
			}
			numOfEvents++;
		}
		pIt = pIt + 1;
	}
}

void Server::handleInfoMessage(pollfdIt pIt, bool &info, Info &messageInfo)
{
	char buffer[sizeof(Info)];
	int received = recv(data[pIt].fd, buffer, sizeof(buffer), 0);
	if (received == -1)
	{
		std::cerr << "error reciving the Info message\n" << "sizeOf: " << sizeof(Info) <<'\n';
		return ;
	}
	std::memcpy(&messageInfo, buffer, sizeof(Info));
	if (messageInfo.flags == FLAG_NEW_ENTITY)
		info = false;
	else if (messageInfo.flags == FLAG_NEW_POSITION)
		info = false;
}

void Server::handleDataMessage(pollfdIt pIt, bool &info, Info &messageInfo)
{
	if (messageInfo.flags == FLAG_NEW_ENTITY)
	{
		char buffer[sizeof(Entity)];
		int received = recv(data[pIt].fd, buffer, sizeof(buffer), 0);
		dataMutex.lock();
		Entity newEntity;
		std::memcpy(&newEntity, buffer, sizeof(Entity));
		data.addEntity(newEntity);
		dataMutex.unlock();
		info = true;
	}
	else if (messageInfo.flags == FLAG_NEW_POSITION)
	{
		
		char buffer[sizeof(glm::vec2)];
		int received = recv(data[pIt].fd, buffer, sizeof(buffer), 0);
		dataMutex.lock();
		glm::vec2 newPos;
		std::memcpy(&newPos, buffer, sizeof(glm::vec2));
		data[(posIt)pIt] = newPos;
	//	std::cout << "new pos [" << newPos.x << ',' << newPos.y << "]\n"; 
		dataMutex.unlock();
		info = true;
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
	events = poll(data.pollData(), static_cast<nfds_t>(data.playerSize()), 100);
	if (data[pIt].revents & POLLIN)
		acceptConnection();
	handleSignals(events);
}

void	Server::sendData()
{
	Info messageInfo = {};
	for (pollfdIt i = 1; i < data.playerSize(); i = i + 1)
	{
		dataMutex.lock();
		messageInfo.flags = FLAG_PLAYER_VECTOR;
		messageInfo.size = data.playerSize() - 1;
		//std::cout << "message info flags " << (int)messageInfo.flags << " size " << (int)messageInfo.size << "\n";
		std::cout << "send pos [" << (data.playersData() + 1)->pos.x << ',' << (data.playersData() + 1)->pos.y << "]\n";
		send(data[i].fd, &messageInfo, sizeof(Info), 0);
		bool sended = false;
		while (!sended)
		{
			if (send(data[i].fd, data.playersData() + 1, sizeof(Entity) * messageInfo.size, 0) == -1)//player pos
			{
			//std::cout << color::boldred << "failed to send info\nsize[" << messageInfo.size << "]\n" << color::reset;
			//std::error_code ec(errno, std::system_category());
			//std::cerr << "fd " << data[i].fd << "size " << sizeof(Entity) * messageInfo.size << "ptr " << data.playersData() + 1 <<  " An error ocurred sending the message: " << color::boldwhite << ec.message() << color::reset << std::endl;
			//std::cout << color::boldred << "failed to send info\nsize[" << messageInfo.size << "]\n" << color::reset;
			//std::cerr << "fd " << data[i].fd << " size " << sizeof(Entity) * messageInfo.size << " ptr " << data.playersData() + 1 <<  '\n';
			//// Print the error message associated with errno
			//std::cerr << "An error occurred sending the message: " << color::boldwhite << strerror(errno) << color::reset << std::endl;
			}
			else
			{
				std::cout << color::green << "sended\n" << color::reset;
				sended = true;
			}
		}
		sended = false;
		messageInfo.flags = FLAG_ENTITY_VECTOR;
		messageInfo.size = data.entitySize() - 1;
		send(data[i].fd, &messageInfo, sizeof(Info), 0);
		send(data[i].fd, &data.entitiesData()[0], sizeof(Entity) * messageInfo.size, 0);//entities pos
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
	data.addUser(new_client.fd);
	Info info = {};
	info.flags = FLAG_ID;
	info.size = data.playerSize() - 2;
	//std::cout << "message info flags " << (int)info.flags << " size " << (int)info.size << "\n";
	if (send(new_client.fd, &info, sizeof(Info), 0) == -1)
		std::cout << color::boldred << "Failed to send info accept connection\n" << color::reset;
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
	data.addUser(serverFd);
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