/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:28:59 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/17 12:12:00 by ecamara          ###   ########.fr       */
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

Entity	*Data::playersData()
{
	return players.data();
}

Entity	*Data::entitiesData()
{
	return entities.data();
}



uint32_t	Data::playerSize() const
{
	return pollfdVector.size();
}

uint32_t	Data::entitySize() const
{
	return entities.size();
}

void	Data::addUser(int fd, std::string username)
{
	pollfd newPollfd;
	newPollfd.fd = fd;
	newPollfd.events = POLLOUT | POLLIN;
	pollfdVector.push_back(newPollfd);
	
	User newUser(username);
	users.push_back(newUser);
	
	Entity newEntity = {};

	EntityData entityData = {};
	entityData.id = players.size() - 1;
	entityData.flags = 0;
	newEntity.data = static_cast<uint64_t>(entityData.id) << 32 | entityData.flags;
	newEntity.pos = {1.1f,-1.1};
	newEntity.vel = {0,0};
	players.push_back(newEntity);
}

void	Data::addEntity(Entity entity)
{
	Entity newEntity = {};

	EntityData entityData = {};
	entityData.id = entities.size() - 1;
	entityData.flags = 0;
	entity.data = static_cast<uint64_t>(entityData.id) << 32 | entityData.flags;
	entities.push_back(entity);
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
	return players[idx].pos;
}

const glm::vec2 &Data::operator[](posIt idx) const
{
	return players[idx].pos;
}

glm::vec2 &Data::operator[](velIt idx)
{
	return players[idx].vel;
}

const glm::vec2 &Data::operator[](velIt idx) const
{
	return players[idx].vel;
}

uint32_t &Data::operator[](idIt idx)
{
	uint64_t& data64 = players[idx].data;
	uint32_t& data32 = reinterpret_cast<uint32_t&>(data64); // alias the data as a 32-bit integer
	return data32; // return the first 32 bits of the 64-bit integer
}

const uint32_t &Data::operator[](idIt idx) const
{
	const uint64_t& data64 = players[idx].data;
	const uint32_t& data32 = reinterpret_cast<const uint32_t&>(data64); // alias the data as a 32-bit integer
	return data32; // return the first 32 bits of the 64-bit integer
}

uint32_t &Data::operator[](flagsIt idx)
{
	uint64_t &data = players[idx].data;
	return reinterpret_cast<uint32_t*>(&data)[1];
}

const uint32_t &Data::operator[](flagsIt idx) const
{
	const uint64_t &data = players[idx].data;
	return reinterpret_cast<const uint32_t*>(&data)[1];
}


Entity &Data::operator[](entityIt idx)
{
	return entities[idx];
}

const Entity &Data::operator[](entityIt idx) const
{
	return entities[idx];
}

