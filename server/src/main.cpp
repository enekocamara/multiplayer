/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 11:12:12 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/22 13:39:04 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/include.h"

#include "../../libraries/GLFW/glfw3.h"

#include "../includes/Server.hpp"

//#include <vulkan/vulkan.h>

//extern "C" {
//#include "../../libraries/mlx/betterMlx.h"
//}

#include <ifaddrs.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netdb.h>
#include <iostream>
#include <fstream>

void printIp()
{
	struct ifaddrs *ifaddr, *ifa;
	if (getifaddrs(&ifaddr) == -1) {
		std::cerr << "getifaddrs failed" << std::endl;
		return ;
	}
	for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == nullptr) {
			continue;
		}
		if (ifa->ifa_addr->sa_family == AF_INET && !(ifa->ifa_flags & IFF_LOOPBACK)) {
			char host[NI_MAXHOST];
			int res = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, nullptr, 0, NI_NUMERICHOST);
			if (res != 0) {
				std::cerr << "getnameinfo failed: " << gai_strerror(res) << std::endl;
			} else {
				std::cout << "IP address: " << host << std::endl;
			}
			break;
		}
	}
	freeifaddrs(ifaddr);
}

void	readConfig(t_config &config)
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

int	main()
{
	printIp();
	ServerCreateInfo udpServerInfo;
	t_config config;
	readConfig(config);
	udpServerInfo.numOfRooms = config.numOfRooms;
	std::cout << "num of rooms :" << config.numOfRooms << "\n";
	udpServerInfo.port = config.port;
	try{
		Server server(udpServerInfo, config);
		server.run();
	}
	catch(const std::exception &e)
	{
		std::cerr << "Error, " << e.what() << '\n';
	}
	return (0);
}