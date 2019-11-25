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
#include "fs_udp.h"
#include "fs_monitor_log.h"

void packet_udp(struct fs_monitor_worker * worker , struct field_linked_list * result) {
	struct fs_udp_packet packet;
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

	INFO_LOG("[读取信息] offset:%d inotofy:%d\n" , worker->offset , worker->notify_fd);

	close_file(fd);
}

void file_deleted(struct fs_monitor_worker * worker) {
	INFO_LOG("文件被删除\n");
}

void file_created(struct fs_monitor_worker * worker) {
	INFO_LOG("文件被创建\n");
}

void file_moved(struct fs_monitor_worker * worker) {
	worker->offset = 0;
}
