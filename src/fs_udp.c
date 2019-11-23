/*
 * fs_udp.c
 *
 *  Created on: Nov 20, 2019
 *      Author: gilbert
 */

#include "fs_udp.h"
#include "fs_access_agent_consts.h"
#include "fs_monitor_log.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int send_to_server(int sock_fd , char * host , int port , struct fs_udp_packet packet) {
	struct sockaddr_in addr;
	addr.sin_family =AF_INET;
	addr.sin_port =htons(port);
	addr.sin_addr.s_addr = inet_addr(host);

	int bytes = -1;
	if (-1 == (bytes = sendto(sock_fd , &packet , sizeof(packet) , 0 , (struct sockaddr*)&addr , sizeof(addr)))) {
		ERROR_LOG("发送错误");

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
		ERROR_LOG("socket创建失败");

		return -1;
	}

	return sock_fd;
}
