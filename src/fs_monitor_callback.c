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
#include "fs_monitor_worker_pool.h"

void packet_udp(struct fs_monitor_worker * worker , struct field_linked_list * result) {
	struct fs_monitor_worker_pool * worker_pool = get_worker_pool();

	char snd_buffer[DEFAULT_LINE_BUUFER_SIZE] = {0};
	char log_buffer[DEFAULT_LINE_BUUFER_SIZE] = {0};
	int size = 0;

	struct field_linked_list * ptr = result;
	int offset = 0;
	int log_offset = 0;
	while (ptr != 0) {
		struct fs_monitor_field_cfg * pfield = worker_pool->field_cfg_list;
		while (pfield != 0) {
			if (pfield->index == ptr->index) {

				log_offset += sprintf(log_buffer + log_offset , "%s|" , ptr->field);

				(void)memcpy(snd_buffer + offset , ptr->field , pfield->size);
				size += pfield->size;

				break;
			}

			pfield = pfield->next;
		}

		ptr = ptr->next;
	}

	printf("发送消息：%s\n" , log_buffer);

	if (-1 == send_to_server(worker->sock_fd , worker->host , worker->port , snd_buffer , size)) {
		ERROR_LOG("发送失败");
	}
}

void synchronize(struct fs_monitor_worker * worker , char * line , char * separator) {
	struct field_linked_list * result = analysis_line(line , separator);

	packet_udp(worker , result);

	free_field_linked_list(result);
}

void file_modified(struct fs_monitor_worker * worker) {
	int fd = open_file(worker->file , worker->offset);

	char line[DEFAULT_LINE_BUUFER_SIZE] = {0};
	int ret = 0;
	while ((ret = read_line(fd , line)) > 0) {
		worker->offset += ret;

		synchronize(worker , line , worker->separator);

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
	INFO_LOG("文件被迁移\n");

	worker->offset = 0;
}
