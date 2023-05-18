/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:46:49 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/18 13:54:08 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ServerData.hpp"

ServerData::ServerData()
{
	IDs.resize(1);
	clientAddress.resize(1);
	clientAddressLength.resize(1);
	numOfClients = 0;
}

ServerData::~ServerData()
{
	
}

const int	*ServerData::getPorts()const
{
	return tempInfo.ports;
}

const char	*ServerData::getIpAddresses()const
{
	return (const char *)tempInfo.ipAddresses;
}

uint8_t		ServerData::getActiveRooms()const
{
	return tempInfo.activeRooms;
}