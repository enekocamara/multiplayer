/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerDefines.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:03:49 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/18 13:25:13 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

#define MAX_ROOMS 8

struct messageInfo{
	uint32_t ID;
	uint32_t size;
};

struct	ServerCreateInfo{
	int	port;
};

struct ServerInfo{
	char		*ipAddresses[15 * MAX_ROOMS];
	int			ports[MAX_ROOMS];
	uint32_t	ID;
	uint8_t		activeRooms;
	uint8_t		maxRooms;
};

namespace color {
	const std::string reset		= "\033[0m";
	const std::string black		= "\033[30m";
	const std::string red		= "\033[31m";
	const std::string green		= "\033[32m";
	const std::string yellow	= "\033[33m";
	const std::string blue		= "\033[34m";
	const std::string magenta	= "\033[35m";
	const std::string cyan		= "\033[36m";
	const std::string white		= "\033[37m";

	const std::string boldblack		=  "\033[1m\033[30m";
	const std::string boldred		=  "\033[1m\033[31m";
	const std::string boldgreen		=  "\033[1m\033[32m";
	const std::string boldyellow	=  "\033[1m\033[33m";
	const std::string boldblue		=  "\033[1m\033[34m";
	const std::string boldmagenta	=  "\033[1m\033[35m";
	const std::string boldcyan		=  "\033[1m\033[36m";
	const std::string boldwhite		=  "\033[1m\033[37m";
	
	const std::string boldgreenback =  "\033[1m\033[42m";
}
