/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:28:43 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/18 11:09:19 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define FLAG_ID            0b00000001
#define FLAG_ENTITY_VECTOR 0b00000010
#define FLAG_PLAYER_VECTOR 0b00000100
#define FLAG_NEW_ENTITY    0b00001000
#define FLAG_NEW_POSITION  0b00010000

#include <iostream>

#include "../glm/glm.hpp"

struct Info{
	uint32_t flags;
	uint32_t size;
};

struct EntityData{
	uint32_t id;
	uint32_t flags;
};

struct Entity{
	glm::vec2 pos;
	glm::vec2 vel;
	uint64_t data;
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


struct userIt{
	uint32_t index;
	userIt(int value = 0):index(value){};
	operator uint32_t() const {
		return index;
	}
	userIt& operator=(uint32_t value){
		index = value;
		return *this;
	}
	userIt& operator++() {
		++index;
		return *this;
	}
};

struct pollfdIt{
	uint32_t index;
	pollfdIt(int value = 0):index(value){};
	operator uint32_t() const {
		return index;
	}
	pollfdIt& operator=(uint32_t value){
		index = value;
		return *this;
	}
	pollfdIt& operator++() {
		++index;
		return *this;
	}
	pollfdIt operator++(int) {
		pollfdIt tmp(*this);
		++index;
		return tmp;
	}
};

struct posIt{
	uint32_t index;
	posIt(int value = 0):index(value){};
	operator uint32_t() const {
		return index;
	}
	posIt& operator=(uint32_t value){
		index = value;
		return *this;
	}
	posIt& operator++() {
		++index;
		return *this;
	}
	posIt operator++(int) {
		posIt tmp(*this);
		++index;
		return tmp;
	}
};

struct idIt{
	uint32_t index;
	idIt(int value = 0):index(value){};
	operator uint32_t() const {
		return index;
	}
	idIt& operator=(uint32_t value){
		index = value;
		return *this;
	}
	idIt& operator++() {
		++index;
		return *this;
	}
	idIt operator++(int) {
		idIt tmp(*this);
		++index;
		return tmp;
	}
};

struct flagsIt{
	uint32_t index;
	flagsIt(int value = 0):index(value){};
	operator uint32_t() const {
		return index;
	}
	flagsIt& operator=(uint32_t value){
		index = value;
		return *this;
	}
	flagsIt& operator++() {
		++index;
		return *this;
	}
	flagsIt operator++(int) {
		flagsIt tmp(*this);
		++index;
		return tmp;
	}
};

struct velIt{
	uint32_t index;
	velIt(int value = 0):index(value){};
	operator uint32_t() const {
		return index;
	}
	velIt& operator=(uint32_t value){
		index = value;
		return *this;
	}
	velIt& operator++() {
		++index;
		return *this;
	}
	velIt operator++(int) {
		velIt tmp(*this);
		++index;
		return tmp;
	}
};

struct entityIt{
	uint32_t index;
	entityIt(int value = 0):index(value){};
	operator uint32_t() const {
		return index;
	}
	entityIt& operator=(uint32_t value){
		index = value;
		return *this;
	}
	entityIt& operator++() {
		++index;
		return *this;
	}
	entityIt operator++(int) {
		entityIt tmp(*this);
		++index;
		return tmp;
	}
};
