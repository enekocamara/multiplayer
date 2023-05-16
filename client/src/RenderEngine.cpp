/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RenderEngine.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecamara <ecamara@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:19:39 by ecamara           #+#    #+#             */
/*   Updated: 2023/05/16 16:31:08 by ecamara          ###   ########.fr       */
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
	initEntityAtlas();
}

RenderEngine::~RenderEngine()
{
	
}

void	RenderEngine::initEntityAtlas()
{
	for (uint32_t i = 0; i < 2; i++)
	{
		t_image entity;
		std::string path =  "textures/entities/entity00" + std::to_string(i) + ".xpm";
		bmlx_create_img_xpm(mlx, &entity, path.c_str(), 16, 16);
		entityAtlas.push_back(entity);
	}
}

void	RenderEngine::createWindow()
{
	std::cout << "window dimensions [" << map.getHeight() << "][" << map.getWidth() << "]\n";
	win = mlx_new_window(mlx, map.getWidth() * TILE, map.getHeight() * TILE, (char *)"multiplayer");
	std::cout << "window self =" << this << "\n";
	if (!win)
	{
		std::cout << "FAILED TO CREATE WINDOW\n";
		exit(1);
	}
}

void	RenderEngine::render()
{
	//std::cout << "render self" << this << "\n";
	//void *temp = reinterpret_cast<void *>(this);
	//std::cout << "reinter self" << temp << "\n";
	//std::cout << "after self" << reinterpret_cast<RenderEngine *>(temp) << "\n";
	createWindow();
	mlx_loop_hook(mlx, renderFrameWrapper, reinterpret_cast<void *>(this));
	mlx_hook(win, 2, 1L << 0, eventspressWrapper,  reinterpret_cast<void *>(this));
	mlx_hook(win, 3, 1L << 0, eventsrealeseWrapper,  reinterpret_cast<void *>(this));
	//mlx_hook(win, 4, 1L << 0, mouseEventWrapper,  reinterpret_cast<void *>(this));
	mlx_mouse_hook(win, mouseEventWrapper,  reinterpret_cast<void *>(this));
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
	//std::cout << "frame self =" << this << "\n";
	updatePosition();
	printFPS();
	mlx_put_image_to_window(mlx, win, map.getMap(), 0,0);
	posMutex->lock();
	for (posIt i = 0; i < data->playersSize(); i++)
	{
		mlx_put_image_to_window(mlx, win, entityAtlas[0].img, (*data)[i].x * TILE, (*data)[i].y * -1 * TILE);
	}
	for (entityIt i = 0; i < data->entitiesSize(); i++)
	{
		mlx_put_image_to_window(mlx, win, entityAtlas[1].img, (*data)[i].pos.x * TILE, (*data)[i].pos.y * -1 * TILE);
	}
	posMutex->unlock();
}

uint32_t RenderEngine::getPosition(glm::vec2 pos)
{
	uint32_t y = (pos.y * -1);
	uint32_t x = pos.x;
	return (y * map.getWidth() + x);
}

void RenderEngine::updatePosition()
{
	float step = 0.05f;
	//std::cout << "x " << data->myPos.x << " y " << data->myPos.y << '\n';
	//std::cout << "my pos value " << map.getValue(getPosition(data->myPos)) << '\n'; 
	if (keyboard.up && !map.getValue(getPosition({data->myPos.x, data->myPos.y + step}))
					&& !map.getValue(getPosition({data->myPos.x + 0.5f, data->myPos.y + step})))
	{
		data->myPos.y += step;
	}
	if (keyboard.down && !map.getValue(getPosition({data->myPos.x, data->myPos.y - step - 0.5f}))
					  && !map.getValue(getPosition({data->myPos.x + 0.5f, data->myPos.y - step - 0.5f})))
	{
		data->myPos.y -= step;
	}
	if (keyboard.left && !map.getValue(getPosition({data->myPos.x - step, data->myPos.y}))
					  && !map.getValue(getPosition({data->myPos.x - step, data->myPos.y - 0.5f})))
	{
		data->myPos.x -= step;
	}
	if (keyboard.right && !map.getValue(getPosition({data->myPos.x + step + 0.5f, data->myPos.y}))
					   && !map.getValue(getPosition({data->myPos.x + step + 0.5f, data->myPos.y - 0.5f})))
	{
		data->myPos.x += step;
	}
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


void	RenderEngine::mouseEvent(int keycode, int x, int y)
{
	if (keycode == 1)
	{
		glm::ivec2 pos;
		//std::cout << "self =" << this << "\n";
		//std::cout << "[" << mlx << "]\n";
		mlx_mouse_get_pos(win, &pos.x, &pos.y);
		std::cout << "fire shuriken[" << x << ',' << y << "]\n";
		Entity shuriken;

		EntityData entityData = {};
		entityData.id = 0;
		entityData.flags = 0;

		shuriken.data = static_cast<uint64_t>(entityData.id) << 32 | entityData.flags;		
		shuriken.pos.x = x;
		shuriken.pos.y = -y;
		client->sendNewEntity(shuriken);
	}
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

int RenderEngine::mouseEventWrapper(int mousecode, int x, int y, void *param)
{
	RenderEngine *renderer = static_cast<RenderEngine *>(param);
	renderer->mouseEvent(mousecode, x, y);
	return 0;
}