/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderEngine.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:19:39 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/12 12:16:22 by ecamara          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RenderEngine.hpp"

RenderEngine::RenderEngine(Data	*data, Client *client, std::mutex *posMutex):mlx(mlx_init())
{
	this->data = data;
	this->client = client;
	keyboard.up = false;
	keyboard.down = false;
	keyboard.left = false;
	keyboard.right = false;
	this->posMutex = posMutex;
}

RenderEngine::~RenderEngine()
{
	
}

void	RenderEngine::createWindow()
{
	std::cout << "window dimensions [" << map.getHeight() << "][" << map.getWidth() << "]\n";
	win = mlx_new_window(mlx, map.getWidth() * TILE, map.getHeight() * TILE, (char *)"multiplayer");
}

void	RenderEngine::render()
{
	createWindow();
	mlx_loop_hook(mlx, renderFrameWrapper, this);
	mlx_hook(win, 2, 1L << 0, eventspressWrapper, this);
	mlx_hook(win, 3, 1L << 0, eventsrealeseWrapper, this);
	mlx_loop(mlx);
}

void printFPS() {
	static int frameCount = 0;
	static auto startTime = std::chrono::steady_clock::now();
	auto endTime = std::chrono::steady_clock::now();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
	
	if (elapsedTime >= 1000) {
		std::cout << "FPS: " << frameCount << std::endl;
		frameCount = 0;
		startTime = endTime;
	}
	frameCount++;
}

void RenderEngine::renderFrame()
{
	//std::cout << "player pos [" << (*data)[0].x << "," << (*data)[0].y << "]\n";
	updatePosition();
	printFPS();
	mlx_put_image_to_window(mlx, win, map.getMap(), 0,0);
	posMutex->lock();
	for (uint32_t i = 0; i < data->size(); i++)
	{
		mlx_put_image_to_window(mlx, win, map.getTexture(2).img, (*data)[i].x * TILE, (*data)[i].y * -1 * TILE);
	}
	posMutex->unlock();
}

void RenderEngine::updatePosition()
{
	if (keyboard.up)
		data->myPos.y += 0.051f;
	if (keyboard.down)
		data->myPos.y -= 0.05f;
	if (keyboard.left)
		data->myPos.x -= 0.05f;
	if (keyboard.right)
		data->myPos.x += 0.05f;
	client->sendNewPosition(data->myPos);
}

void	RenderEngine::eventpress(int keycode)
{
	if (keycode == 13)
		keyboard.up = true;
	else if (keycode == 0)
		keyboard.left = true;
	else if (keycode == 1)
		keyboard.down = true;
	else if (keycode == 2)
		keyboard.right = true;
}

void	RenderEngine::eventrealese(int keycode)
{
	if (keycode == 13)
		keyboard.up = false;
	else if (keycode == 0)
		keyboard.left = false;
	else if (keycode == 1)
		keyboard.down = false;
	else if (keycode == 2)
		keyboard.right = false;
}


int RenderEngine::renderFrameWrapper(void *param)
{
	RenderEngine *renderer = static_cast<RenderEngine *>(param);
	renderer->renderFrame();
	return 0;
}

int RenderEngine::eventspressWrapper(int keycode, void *param)
{
	RenderEngine *renderer = static_cast<RenderEngine *>(param);
	renderer->eventpress(keycode);
	return 0;
}

int RenderEngine::eventsrealeseWrapper(int keycode, void *param)
{
	RenderEngine *renderer = static_cast<RenderEngine *>(param);
	renderer->eventrealese(keycode);
	return 0;
}