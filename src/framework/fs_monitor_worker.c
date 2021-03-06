/*
 * fs_monitor_worker_pool.c
 *
 *  Created on: Nov 21, 2019
 *      Author: gilbert
 */

#include "fs_monitor.h"
#include "fs_monitor_worker.h"
#include "fs_monitor_worker_pool.h"
#include "fs_monitor_log.h"
#include "fs_monitor_util.h"
#include "fs_monitor_sys_cfg.h"

#include <sys/inotify.h>
#include <string.h>
#include <stdlib.h>

void run_worker_loop(struct fs_monitor_worker_pool * worker_pool) {
	fs_changed_monitor(worker_pool);
}

struct fs_monitor_worker * create_worker(char * dir , char * file , long separator) {
	struct fs_monitor_worker * worker = (struct fs_monitor_worker *)malloc(sizeof(struct fs_monitor_worker));

	if (get_fs_monitor_sys_cfg()->is_from_begin) {
		worker->offset = 0;
	} else {
		worker->offset = get_file_size(file);
	}

	worker->next = 0;
	(void)strcpy(worker->dir , dir);
	(void)strcpy(worker->file , file);
	worker->separator = separator;
	worker->sampling_rate_ctr = 0;

	worker->notify_fd = inotify_init();
	if (worker->notify_fd == -1) {
		ERROR_LOG("初始化inotify失败");

		free(worker);

		return 0;
	}

	worker->watch_dog = inotify_add_watch(worker->notify_fd , worker->dir , IN_ALL_EVENTS);
	if (worker->watch_dog == -1) {
		ERROR_LOG("初始化watch dog失败");

		free(worker);

		return 0;
	}

	return worker;
}
