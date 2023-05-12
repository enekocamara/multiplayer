/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:28:59 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/12 12:14:13 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Data.hpp"

Data::Data()
{
	
}

Data::~Data()
{
	
}

pollfd	*Data::pollData()
{
	return pollfdVector.data();
}

User	*Data::userData()
{
	return users.data();
}

glm::vec2	*Data::posData()
{
	return positions.data();
}


uint32_t	Data::size() const
{
	return pollfdVector.size();
}

void	Data::add(int fd, std::string username)
{
	pollfd newPollfd;
	User newUser(username);

	newPollfd.fd = fd;
	newPollfd.events = POLLOUT | POLLIN;
	pollfdVector.push_back(newPollfd);
	users.push_back(newUser);
	positions.push_back(glm::vec2(1.f,-1.f));
}

User &Data::operator[](userIt idx)
{
	return users[idx];
}

const User &Data::operator[](userIt idx) const
{
	return users[idx];
}

pollfd &Data::operator[](pollfdIt idx)
{
	return pollfdVector[idx];
}

const pollfd &Data::operator[](pollfdIt idx) const
{
	return pollfdVector[idx];
}

glm::vec2 &Data::operator[](posIt idx)
{
	return positions[idx];
}

const glm::vec2 &Data::operator[](posIt idx) const
{
	return positions[idx];
}



