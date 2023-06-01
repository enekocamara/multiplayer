/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:02:42 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/22 15:36:50 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client(UdpClientCreateInfo udpClientCreateInfo) : udpClientCreateInfo(udpClientCreateInfo)
{
	
}

Client::~Client()
{
	
}

void	Client::start()
{
	serverInfo = udpClient.start();
	udpClient.join(0);
	//renderer.createWindow();
	
	//std::thread updateThread(&Client::updateData, this);
	renderer.render();
//	updateThread.join();
}
