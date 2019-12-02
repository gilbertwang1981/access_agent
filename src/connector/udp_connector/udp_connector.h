/*
 * udp_connector.h
 *
 *  Created on: Dec 2, 2019
 *      Author: gilbert
 */

#ifndef _CONNECTOR_UDP_CONNECTOR_UDP_CONNECTOR_H_
#define _CONNECTOR_UDP_CONNECTOR_UDP_CONNECTOR_H_

int send_to_server(int sock_fd , char * host , int port , char * buffer , int size);

int init_net();

int destory_net(int sock_fd);

extern int connnect_to_source(char * snd_buffer , int buffer_size , char * logbuffer);

#endif /* _CONNECTOR_UDP_CONNECTOR_UDP_CONNECTOR_H_ */
