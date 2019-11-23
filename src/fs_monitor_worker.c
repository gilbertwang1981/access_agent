/*
 * fs_monitor_worker_pool.c
 *
 *  Created on: Nov 21, 2019
 *      Author: gilbert
 */

#include "fs_udp.h"
#include "fs_monitor.h"
#include "fs_monitor_worker.h"
#include "fs_monitor_worker_pool.h"
#include "fs_monitor_log.h"

#include <sys/inotify.h>
#include <string.h>
#include <stdlib.h>

void run_worker_loop(struct fs_monitor_worker_pool * worker_pool) {
	fs_changed_monitor(worker_pool);
}

struct fs_monitor_worker * create_worker(char * dir , char * file , char * host , int port) {
	struct fs_monitor_worker * worker = (struct fs_monitor_worker *)malloc(sizeof(struct fs_monitor_worker));

	worker->offset = 0;
	worker->next = 0;
	worker->port = port;
	(void)strcpy(worker->host , host);
	(void)strcpy(worker->dir , dir);
	(void)strcpy(worker->file , file);

	worker->sock_fd = init_net();
	if (worker->sock_fd == -1) {
		ERROR_LOG("初始化udp socket失败");

		free(worker);

		return 0;
	}

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
