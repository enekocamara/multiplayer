/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:59:54 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/22 15:14:34 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <fcntl.h>
#include <thread>
#include <mutex>

#include "RenderEngine.hpp"
#include "Data.hpp"

#include "../../libraries/glm/glm.hpp"
#include "../../libraries/includes/header.h"
#include "../../libraries/UDP/includes/UdpConnection.h"

class Client
{
	public:
		Client(UdpClientCreateInfo udpClientCreateInfo);
		~Client();
		void	start();
		void	sendNewPosition(glm::vec2 newPos);
		void	sendNewEntity(Entity entity);
	private:
		void	pollHandle();
		void	handleInfoMessage(bool &info, Info &messageInfo);
		void	handleDataMessage(bool &info, Info &messageInfo);
		void	updateData();
		

		uint32_t		id;
		int				port;
		pollfd			pollfd;
		std::string		ipAddress;
		sockaddr_in		address;
		std::mutex		posMutex;
		ServerInfo		serverInfo;
		UdpClientCreateInfo		udpClientCreateInfo;
		
		Data			data{};
		UdpClient		udpClient{udpClientCreateInfo};
		RenderEngine	renderer{&data, this, &posMutex};
};