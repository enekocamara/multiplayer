/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:58:46 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/22 11:53:22 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

int	main(int argc, char **argv)
{
	UdpClientCreateInfo udpClientCreateInfo = {};
	
	if (argc != 3)
		return EXIT_FAILURE;
	try{
		udpClientCreateInfo.port = atoi(argv[1]);
		udpClientCreateInfo.ip = argv[2];
		Client  *client = new Client(udpClientCreateInfo);
		client->start();
	}catch(std::exception &e)
	{
		std::cerr << "Error, " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}