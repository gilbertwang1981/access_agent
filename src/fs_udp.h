/*
 * fs_udp.h
 *
 *  Created on: Nov 20, 2019
 *      Author: gilbert
 */

#ifndef _FS_UDP_H_
#define _FS_UDP_H_

#include "fs_access_agent_consts.h"

int send_to_server(int sock_fd , char * host , int port , char * buffer , int size);

int init_net();

int destory_net(int sock_fd);

#endif /* _FS_UDP_H_ */
