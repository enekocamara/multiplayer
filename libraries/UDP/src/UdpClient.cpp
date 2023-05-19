#include "../includes/UdpClient.hpp"

UdpClient::UdpClient(UdpClientCreateInfo info)
{
	socketFd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketFd == -1) {
		throw std::runtime_error("failed to create socket");
	}

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(info.port);
	inet_pton(AF_INET, info.ip.c_str(), &(serverAddress.sin_addr));
}

UdpClient::~UdpClient()
{
	close(socketFd);
}

void UdpClient::start()
{
	handShake();
}

void UdpClient::handShake()
{
	sendHandShake();
	receiveHandShake();
	confirmHandShake();
	finishHandShake();
}

void UdpClient::sendHandShake()
{
	char buffer[sizeof(uint32_t)];
	memset(buffer, 0, sizeof(buffer));
	ssize_t bytesSent = sendto(socketFd, buffer, sizeof(uint32_t), 0,
			(struct sockaddr*)&serverAddress, sizeof(serverAddress));//init handshake
	if (bytesSent == -1)
	{
		std::cerr << color::red << "Failed to init handshake\n" << color::reset;
		exit(1);
	}
	std::cout << color::green << "handshake initiated\n" << color::reset;
}

void	UdpClient::receiveHandShake()
{
	char buffer[sizeof(ServerInfo)];
	socklen_t serverAddressLength = sizeof(serverAddress);
	ssize_t bytesRead = recvfrom(socketFd, buffer, sizeof(buffer), 0,
				(struct sockaddr*)&serverAddress, &serverAddressLength);
	if (bytesRead == -1)
	{
		std::cerr << color::red << "Failed to receive handshake\n" << color::reset;
		exit(1);
	}
	ServerInfo info = {};
	memcpy(&info, buffer, sizeof(ServerInfo));
	parseServerInfo(info);
}

void	UdpClient::parseServerInfo(ServerInfo &info)
{
	serverInfo = info;
	myID = info.ID;
	std::cout << color::boldgreen << "MY ID is: " << info.ID << "\n" << color::reset;
}

void	UdpClient::confirmHandShake()
{
	char buffer[sizeof(uint32_t)];
	memcpy(buffer, &myID, sizeof(buffer));
	ssize_t bytesSent = sendto(socketFd, buffer, sizeof(uint32_t), 0,
			(struct sockaddr*)&serverAddress, sizeof(serverAddress));//init handshake
	if (bytesSent == -1)
	{
		std::cerr << color::red << "Failed to init handshake\n" << color::reset;
		exit(1);
	}
	std::cout << color::green << "handshake confirmed \n" << color::reset;
}

void	UdpClient::finishHandShake()
{
	char buffer[sizeof(uint32_t)];
	socklen_t serverAddressLength = sizeof(serverAddress);
	ssize_t bytesRead = recvfrom(socketFd, buffer, sizeof(buffer), 0,
				(struct sockaddr*)&serverAddress, &serverAddressLength);
	if (bytesRead == -1)
	{
		std::cerr << color::red << "Failed to receive handshake\n" << color::reset;
		exit(1);
	}
	uint32_t checkId;
	memcpy(&checkId, buffer, sizeof(uint32_t));
	if (checkId == myID)
		std::cout << color::green << "ID correctly set\n" << color::reset;
	else
	{
		std::cerr << color::red << "ID's do not match\n" << color::reset;
		exit(1);
	}
	ssize_t bytesSent = sendto(socketFd, buffer, sizeof(uint32_t), 0,
			(struct sockaddr*)&serverAddress, sizeof(serverAddress));//init handshake
	if (bytesSent == -1)
	{
		std::cerr << color::red << "Failed to init handshake\n" << color::reset;
		exit(1);
	}
	std::cout << color::green << "handshake finished \n" << color::reset;
	serverInfo.print();
}