/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:58:46 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/16 14:41:32 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

int	main(int argc, char **argv)
{
	if (argc != 3)
		return EXIT_FAILURE;
	try{
		Client  *client = new Client(atoi(argv[1]), argv[2]);
		client->start();
	}catch(std::exception &e)
	{
		std::cerr << "Error, " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}