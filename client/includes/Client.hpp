/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:59:54 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/12 12:25:47 by ecamara          ###   ########.fr       */
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
#include "include.h"
#include "../../libraries/glm/glm.hpp"



class Client
{
	public:
		Client(int port, std::string ipAddress);
		~Client();
		void	start();
		void	sendNewPosition(glm::vec2 newPos);
	private:
		void	pollHandle();
		void	updateData();
		uint32_t		id;
		int				port;
		pollfd			pollfd;
		std::string		ipAddress;
		sockaddr_in		address;
		std::mutex		posMutex;
		Data			data{};
		RenderEngine	renderer{&data, this, &posMutex};
};