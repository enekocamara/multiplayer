/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:49:58 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/19 13:42:09 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>
#include <mutex>
#include <chrono>

#include "../includes/Data.hpp"
#include "../../libraries/includes/header.h"
#include "../../libraries/UDP/includes/UdpConnection.h"

#include <netinet/tcp.h>

struct t_config{
	int port;
	uint32_t	flags;
	uint32_t	maxUsers;
	uint32_t	queueSize;
	uint32_t	numOfRooms;
	std::string	name;
	struct sockaddr_in address;

	void update(std::string &line)
	{
		uint32_t index = line.find('=');
		std::string key = line.substr(0,index);
		if (key == "name")
			name = line.substr(index + 1, line.size() - index + 1);
		else if (key == "port")
			port = atoi(line.substr(index + 1, line.size() - index + 1).c_str());
		else if (key == "maxUsers")
			maxUsers = atoi(line.substr(index + 1, line.size() - index + 1).c_str());
		else if (key == "queueSize")
			queueSize = atoi(line.substr(index + 1, line.size() - index + 1).c_str());
		else if(key == "numOfRooms")
			numOfRooms = atoi(line.substr(index + 1, line.size() - index + 1).c_str());
	}
};

class Server{
	public:
		Server(ServerCreateInfo UdpServerInfo, t_config config);
		~Server();
		void	run();
	private:
		void	sendData();
		void	pollHandler();
		void	readConfig();
		void	setSocket();
		void	listenConnection();
		void	acceptConnection();

		void	handleSignals(int max);
		void	handleInfoMessage(pollfdIt pIt, bool &info, Info &messageInfo);
		void	handleDataMessage(pollfdIt pIt, bool &info, Info &messageInfo);
		
		t_config			config;
		ServerCreateInfo	UdpServerCreateInfo;
		UdpServer	udpServer{UdpServerCreateInfo};
		Data		data;
		std::mutex dataMutex;
};