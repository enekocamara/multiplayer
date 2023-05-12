/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:23:06 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/12 13:54:55 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../../libraries/glm/glm.hpp"
#include <vector>
#include <iostream>

#include "include.h"

class Data{
	public:
		Data();
		~Data();
		uint32_t	size()const;
		void	update(char *buffer, uint32_t size);
		glm::vec2 &operator[](uint32_t idx);
		glm::vec2	myPos{1.1f,-1.1};
	private:
		std::vector<glm::vec2>positions;
};