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
#include "fs_monitor_log.h"
#include "fs_monitor_sys_cfg.h"
#include "fs_monitor_worker_pool.h"
#include "fs_monitor_filter_cfg.h"

int is_filter_success(char * field_key , char * field_value) {
	struct fs_monitor_filter_cfg * filter_cfg = get_fs_monitor_filter_cfg();
	while (filter_cfg != 0) {
		if (strcmp(filter_cfg->filter_key , field_key) == 0) {
			if (strcmp(field_value , filter_cfg->filter_value) == 0) {
				return 1;
			} else {
				return 0;
			}
		}

		filter_cfg = filter_cfg->next;
	}

	return 1;
}

void do_execute_connector(struct fs_monitor_worker * worker , struct field_linked_list * result) {
	struct fs_monitor_worker_pool * worker_pool = get_worker_pool();

	char snd_buffer[DEFAULT_LINE_BUFFER_SIZE] = {0};
	char log_buffer[DEFAULT_LINE_BUFFER_SIZE] = {0};
	int size = 0;

	struct field_linked_list * ptr = result;
	int offset = 0;
	int log_offset = 0;
	int is_filtered = 0;
	while (ptr != 0) {
		struct fs_monitor_field_cfg * pfield = worker_pool->field_cfg_list;
		while (pfield != 0) {
			if (pfield->index == ptr->index) {
				if (is_filter_success(pfield->field , ptr->field) == 0) {
					is_filtered = 1;
				}

				log_offset += sprintf(log_buffer + log_offset , "%s|" , ptr->field);

				(void)memcpy(snd_buffer + offset , ptr->field , pfield->size);
				size += pfield->size;

				break;
			}

			pfield = pfield->next;
		}

		ptr = ptr->next;
	}

	if (is_filtered == 0 && strlen(log_buffer) > 0) {
		get_worker_pool()->connector_callback_func(snd_buffer , size , log_buffer);
	}
}

void synchronize(struct fs_monitor_worker * worker , char * line , long separator) {
	struct field_linked_list * result = analysis_line(line , separator);

	do_execute_connector(worker , result);

	free_field_linked_list(result);
}

int is_should_read(struct fs_monitor_worker * worker) {
	struct fs_monitor_sys_cfg * sys_cfg = get_fs_monitor_sys_cfg();
	if (worker->sampling_rate_ctr >= 100) {
		worker->sampling_rate_ctr = 0;
	}

	int step = (int)(100 / sys_cfg->sampling_rate);
	if (worker->sampling_rate_ctr ++ % step == 0) {
		return 1;
	} else {
		return 0;
	}
}

void file_modified(struct fs_monitor_worker * worker) {
	int fd = open_file(worker->file , worker->offset);

	char line[DEFAULT_LINE_BUFFER_SIZE] = {0};
	int ret = 0;
	while ((ret = read_line(fd , line)) > 0) {
		worker->offset += ret;

		if (is_should_read(worker)) {
			synchronize(worker , line , worker->separator);
		}

		(void)memset(line , 0x00 , DEFAULT_LINE_BUFFER_SIZE);
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
