/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ThreadedServer.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 11:58:10 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/19 12:57:04 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ThreadedServer.hpp"

ThreadedServer::ThreadedServer(int port) : port(port)
{
	socketFd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketFd == -1) {
		throw std::runtime_error("failed to create socket");
	}
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(port);  // Port number
	sockaddr.sin_addr.s_addr = INADDR_ANY;  // Bind to all available network interfaces

	if (bind(socketFd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == -1) {
		close(socketFd);
		throw std::runtime_error("failed to bind socket");
	}
}

ThreadedServer::~ThreadedServer()
{
	
}