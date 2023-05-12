/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:29:25 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/12 12:13:51 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libraries/glm/glm.hpp"

#include <iostream>
#include <vector>
#include <poll.h>
#include "User.hpp"

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
};

class Data{
	public:
		Data();
		~Data();
		pollfd		*pollData();
		User		*userData();
		glm::vec2	*posData();
		
		uint32_t	size() const;
		
		User &operator[](userIt idx);
		const User &operator[](userIt idx) const;
		pollfd &operator[](pollfdIt idx);
		const pollfd &operator[](pollfdIt idx) const;
		glm::vec2 &operator[](posIt idx);
		const glm::vec2 &operator[](posIt idx) const;

		void		add(int fd, std::string username  = "nobody");
		pollfdIt p_begin();
		userIt u_begin();
	private:
		std::vector<pollfd> pollfdVector;
		std::vector<User> users;
		std::vector<glm::vec2>positions;
};