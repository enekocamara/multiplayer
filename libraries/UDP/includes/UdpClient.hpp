/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UdpClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:44:40 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/19 14:50:59 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "StaticColor.hpp"
#include "ServerDefines.hpp"
struct	UdpClientCreateInfo{
	int	port;
	std::string ip;
};

class UdpClient{
	public:
		UdpClient(UdpClientCreateInfo info);
		~UdpClient();

		void	start();
	private:
		void	handShake();
		void	sendHandShake();
		void	confirmHandShake();
		void	receiveHandShake();
		void	finishHandShake();
		void	parseServerInfo(ServerInfo &info);
		
		int		socketFd;
		uint32_t myID;
		struct	sockaddr_in serverAddress;
		ServerInfo serverInfo;
};