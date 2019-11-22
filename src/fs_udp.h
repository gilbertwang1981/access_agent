/*
 * fs_udp.h
 *
 *  Created on: Nov 20, 2019
 *      Author: gilbert
 */

#ifndef _FS_UDP_H_
#define _FS_UDP_H_

#include "fs_access_agent_consts.h"

struct fs_udp_packet {
	char forward_ip[DEFAULT_IP_ADDRESS_LEN];
	char client_ip[DEFAULT_IP_ADDRESS_LEN];
	char method[DEFAULT_METHOD_LEN];
	char status[DEFAULT_STATUS_LEN];
	char interface[DEFAULT_STR_LEN];
	char service[DEFAULT_STR_LEN];
	char time[DEFAULT_TIME_LEN];
	char resp_time[DEFUALT_RESP_TIME_LEN];
};

int send_to_server(int sock_fd , char * host , int port , struct fs_udp_packet packet);

int init_net();

int destory_net(int sock_fd);

#endif /* _FS_UDP_H_ */
