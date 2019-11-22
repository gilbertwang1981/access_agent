/*
 * fs_monitor_callback.c
 *
 *  Created on: Nov 19, 2019
 *      Author: gilbert
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fs_monitor_callback.h"
#include "fs_access_agent_consts.h"
#include "fs_log_field.h"
#include "fs_udp.h"

void packet_udp(struct fs_monitor_worker * worker , struct field_linked_list * result) {
	char forward_ip[DEFAULT_STR_LEN] = {0};
	get_forward_ip(result , forward_ip);

	char client_ip[DEFAULT_STR_LEN] = {0};
	get_client_ip(result , client_ip);

	char method[DEFAULT_STR_LEN] = {0};
	get_method(result , method);

	char status[DEFAULT_STR_LEN] = {0};
	get_status(result , status);

	char interface[DEFAULT_STR_LEN] = {0};
	get_interface(result , interface);

	char service[DEFAULT_STR_LEN] = {0};
	get_service_host(result , service);

	char time[DEFAULT_STR_LEN] = {0};
	get_timestamp(result , time);

	char resp_time[DEFAULT_STR_LEN] = {0};
	get_resp_time(result , resp_time);

	printf("[提取信息]forward ip:%s client ip:%s method:%s status:%s interface:%s service:%s time:%s response time:%s\n" ,
			forward_ip , client_ip , method , status , interface , service , time , resp_time);

	struct fs_udp_packet packet;
	(void)strcpy(packet.client_ip , client_ip);
	(void)strcpy(packet.forward_ip , forward_ip);
	(void)strcpy(packet.interface , interface);
	(void)strcpy(packet.method , method);
	(void)strcpy(packet.resp_time , resp_time);
	(void)strcpy(packet.service , service);
	(void)strcpy(packet.status , status);
	(void)strcpy(packet.time , time);

	if (-1 == send_to_server(worker->sock_fd , worker->host , worker->port , packet)) {
		perror("发送失败");
	}
}

void synchronize(struct fs_monitor_worker * worker , char * line) {
	struct field_linked_list * result = analysis_line(line);

	packet_udp(worker , result);

	free_field_linked_list(result);
}

void file_modified(struct fs_monitor_worker * worker) {
	int fd = open_file(worker->file , worker->offset);

	char line[DEFAULT_LINE_BUUFER_SIZE] = {0};
	int ret = 0;
	while ((ret = read_line(fd , line)) > 0) {
		worker->offset += ret;

		synchronize(worker , line);

		(void)memset(line , 0x00 , DEFAULT_LINE_BUUFER_SIZE);
	}

	printf("[读取信息] offset:%d inotofy:%d\n" , worker->offset , worker->notify_fd);

	close_file(fd);
}

void file_deleted(struct fs_monitor_worker * worker) {
	printf("文件被删除\n");
}

void file_created(struct fs_monitor_worker * worker) {
	printf("文件被创建\n");
}

void file_moved(struct fs_monitor_worker * worker) {
	worker->offset = 0;
}
