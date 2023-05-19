/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 13:02:42 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/19 17:12:46 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client(int port, std::string ipAddress)
{
	
}

Client::~Client()
{
	
}

void	Client::start()
{
	//renderer.createWindow();
	
	//std::thread renderThread(&RenderEngine::render, &renderer);
	std::thread updateThread(&Client::updateData, this);
	renderer.render();
	updateThread.join();
}
