/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderEngine.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:17:23 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/22 15:39:41 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

extern "C" {
#include "../../libraries/mlx/betterMlx.h"
}

#include "../../libraries/includes/header.h"

#include "Map.hpp"
#include "Data.hpp"
#include <chrono>
#include <mutex>
#include <vector>

struct Keyboard{
	bool up;
	bool down;
	bool left;
	bool right;
};


class Client;

class RenderEngine{
	public:
		RenderEngine(Data *data, Client *client, std::mutex *posMutex);
		~RenderEngine();
		
		void		render();
		void		renderFrame();
		
		void		sendEntity(Entity &entity);
		
		void		eventpress(int keycode);
		void		eventrealese(int keycode);
		void		mouseEvent(int mousecode, int x, int y);
		void		windowClosed();

		static int	windowClosedWrapper(void *param);
		static int	renderFrameWrapper(void *param);
		static int	eventspressWrapper(int keycode, void *param);
		static int	eventsrealeseWrapper(int keycode, void *param);
		static int	mouseEventWrapper(int mousecode, int x, int y, void *param);
		
		void		createWindow();
		void		updatePosition();
		void		initEntityAtlas();
		
		uint32_t	getPosition(glm::vec2 pos);
	private:
		void	*mlx;
		void	*win;
		Data	*data;
		Client	*client;
		std::mutex *posMutex;
		Keyboard		keyboard;
		Map		map{mlx, "maps/map1.mp"};
		std::vector<t_image>entityAtlas;
};

#include "Client.hpp"