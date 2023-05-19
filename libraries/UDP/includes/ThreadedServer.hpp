/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ThreadedServer.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:18:01 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/19 17:04:34 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <exception>

#include "StaticColor.hpp"

class ThreadedServer{
	public:
		ThreadedServer(int port);
		~ThreadedServer();
		void	run();
	private:
		int	port;
		int	socketFd;
		sockaddr_in	sockaddr;
};