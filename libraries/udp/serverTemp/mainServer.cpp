/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:36:15 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/18 13:58:52 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/UdpServer.hpp"
#include <iostream>
#include <exception>

int main()
{
	ServerCreateInfo info = {};
	info.port = 12345;

	UdpServer *server;
	try{
		server = new UdpServer(info);
		server->run();
	}
	catch(std::exception &e){
		e.what();
		return 1;
	}
	delete server;
	return 0;
}