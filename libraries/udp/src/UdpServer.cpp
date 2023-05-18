#include "../includes/UdpServer.hpp"

UdpServer::UdpServer(ServerCreateInfo info):info(info)
{

}

UdpServer::~UdpServer()
{

}

void UdpServer::run()
{
	std::thread handShakeThread([this]() {
		handShakeServer.run();
	});
	handShakeThread.join();
}

const char	* UdpServer::getIpAddresses()const
{
	return data.getIpAddresses();
}

const int	*UdpServer::getPorts()const
{
	return data.getPorts();
}

uint8_t UdpServer::getActiveRooms()const
{
	return data.getActiveRooms();
}