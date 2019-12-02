/*
 * udp_connector.c
 *
 *  Created on: Dec 2, 2019
 *      Author: gilbert
 */

#include "udp_connector.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

static int connector_udp_sock_fd = -1;

int send_to_server(int sock_fd , char * host , int port , char * buffer , int size) {
	struct sockaddr_in addr;
	addr.sin_family =AF_INET;
	addr.sin_port =htons(port);
	addr.sin_addr.s_addr = inet_addr(host);

	int bytes = -1;
	if (-1 == (bytes = sendto(sock_fd , buffer , size , 0 , (struct sockaddr*)&addr , sizeof(addr)))) {
		return -1;
	}

	return bytes;
}

int destory_net(int sock_fd) {
	if (sock_fd != -1) {
		(void)close(sock_fd);
		sock_fd = -1;

		return 0;
	}

	return -1;
}

int init_net() {
	int sock_fd = socket(AF_INET,SOCK_DGRAM,0);
	if (sock_fd == -1) {
		return -1;
	}

	return sock_fd;
}

int connnect_to_source(char * snd_buffer , int buffer_size , char * logbuffer) {
	printf("UDP connector，消息内容：%s\n" , logbuffer);

	if (connector_udp_sock_fd == -1) {
		connector_udp_sock_fd = init_net();
		if (connector_udp_sock_fd == -1) {
			return -1;
		}
	}

	return send_to_server(connector_udp_sock_fd , "127.0.0.1" , 10012 , snd_buffer , buffer_size);
}
