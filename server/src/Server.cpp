/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:48:49 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/19 17:02:54 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"
#include <fstream>
#include <string>

Server::Server(ServerCreateInfo UdpServerInfo, t_config config):UdpServerCreateInfo(UdpServerInfo), config(config)
{
	
}

Server::~Server()
{
	
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
	std::vector<std::thread> serverThreads;
	serverThreads.emplace_back([this](){
		udpServer.runHandShakeServer();
	});
	for(uint8_t i = 0;i < config.numOfRooms; i++)
	{
		serverThreads.emplace_back([this, i](){
			udpServer.runServer(i);
		});
	}
	for (auto& thread : serverThreads) {
		thread.join();
	}
}
