
#include "mainClient.hpp"

int main(void)
{
	// Create a socket
	int clientSocket;

	(void)request1;
	(void)request2;
	(void)request3;
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1)
	{
		std::cerr << "Error: Failed to create socket\n";
		return (1);
	}

	// Server address
	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8002); // Port number of the server
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP address of the server

	// Connect to the server
	if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
	{
		std::cerr << "Error: Connection failed\n";
		close(clientSocket);
		return (1);
	}
	// Send data to the server
	const char	*message = "\n\r\n\nGET http://localhost/cgitest/test1.cgi/upload/additional/pa%2eth/and?query=42 HTTP/1.1\r\n"
							"Host: s\r\n"
							"User-Agent: Mozilla/5.0\n"
							"Accept: text/html, */*\r\n"
							"Accept-Language: en-us\n"
							"Accept-Charset: \tISO-8859-1,utf-8\n"
							"Connection: keep-alive , idk\r\n"
							"Keep-Alive: max=100, timeout=30\n"
							"Content-Length: 11\n"
							"Content-Type: application/sth ; hello\n"
							// "Expect: 100-continue\n\n"
							// "Transfer-Encoding: chunked\n"
							"\n"
							"1234567890a"
							"GET /tours HTTP/1.1\r\n"
							"Host: localhost\r\n"
							"User-Agent: Mozilla/5.0\n"
							"Accept: text/html, */*\r\n"
							"Expect: 100-continue\n";
	const char *message1 = "Accept-Language: en-us\n"
							"Accept-Charset: \tISO-8859-1,utf-8\n"
							"Connection: keep-alive , \r\n"
							"Keep-Alive: max=100,timeout=30\n"
							"Transfer-Encoding: chunked\n"
							"t: €h\n"
							"\r\n"
							"8;\n"
							"Chromi\r\n\n"
							"12\r\n"
							"Developers Network\r\n"
							"0\r\n"
							"\r\n"
							"GET /../file_in_docs.html HTTP/1.1\r\n"
							"Host: localhost\r\n"
							"User-Agent: Mozilla/5.0\n"
							"Accept: text/html, */*\r\n"
							"Accept-Language: en-us\n"
							"Accept-Charset: \tISO-8859-1,utf-8\n"
							"Connection: keep-alive , \r\n"
							"Keep-Alive: max=100,timeout=30\n"
							"Transfer-Encoding: chunked\n"
							"t: €h\n"
							"\r\n"
							"8;\n"
							"Chromium\r\n"
							"12\r\n"
							"Developers Network\r\n"
							"0\r\n"
							"\r\n"
							;
	if (send(clientSocket, message, strlen(message), 0) == -1)
	{
		std::cerr << "Error: Failed to send data\n";
		close(clientSocket);
		return (1);
	}
	sleep(2);
	if (send(clientSocket, message1, strlen(message1), 0) == -1)
	{
		std::cerr << "Error: Failed to send data\n";
		close(clientSocket);
		return (1);
	}

	// Receive response from the server
	char buffer[8192] = {0};
	sleep(2);
	if (recv(clientSocket, buffer, 8192, 0) == -1)
	{
		std::cerr << "Error: Failed to receive data\n";
		close(clientSocket);
		return (1);
	}
	std::cout << "Server response: " << buffer << std::endl;

	// Close the socket
	close(clientSocket);
	return (0);
}


