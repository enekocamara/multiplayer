/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:34:03 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/10 14:07:13 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

class User
{
	public:
		User(std::string username);
		~User();
		
	private:
		//int fd;
		std::string name;
		std::string username;
};