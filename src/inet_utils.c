#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <ctype.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "info.h"

int sockfd;

int sendStr(char *str) {
	int len = -2;
	len = send(sockfd, str, strlen(str), 0);
	return len;
}

int connectSocket() {
	const uint32_t port = 5000; // port

	struct hostent *host_info;
	host_info = gethostbyname(URL);
	const char *server = host_info->h_name;

	sockfd = 0;

	struct sockaddr_in serv_addr;

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		#ifdef DEBUG
			perror("Error in socket creation\n");
		#endif
		return 0;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	if(inet_pton(AF_INET, server, &serv_addr.sin_addr) <= 0) {
		#ifdef DEBUG
			perror("Error in address binding\n");
		#endif
		return 0;
	}

	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		#ifdef DEBUG
			perror("Error while connecting\n");
		#endif
		return 0;
	}

	return 1;
}
