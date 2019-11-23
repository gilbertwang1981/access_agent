/*
 * fs_monitor_worker_pool.c
 *
 *  Created on: Nov 22, 2019
 *      Author: gilbert
 */


#include "fs_monitor_worker_pool.h"
#include "fs_monitor_log.h"

#include <string.h>

static struct fs_monitor_worker_pool worker_pool;

int init_worker_pool(char * pool_name , int pool_max_size , char * cfg_path) {
	worker_pool.pool_max_size = pool_max_size;

	(void)strcpy(worker_pool.pool_name , pool_name);

	worker_pool.worker_list = 0;

	worker_pool.cfg_list = read_cfg(cfg_path);

	struct fs_monitor_cfg * cfg_ptr = worker_pool.cfg_list;
	while (cfg_ptr != 0) {
		struct fs_monitor_worker * worker = 0;
		if (0 == (worker = create_worker(cfg_ptr->dir , cfg_ptr->file , cfg_ptr->host , cfg_ptr->port))) {
			ERROR_LOG("初始化任务失败");

			return -1;
		}

		add_worker_to_pool(worker);

		cfg_ptr = cfg_ptr->next;
	}

	run_worker_loop(&worker_pool);

	return 0;
}

void add_worker_to_pool(struct fs_monitor_worker * worker) {
	if (worker_pool.worker_list == 0) {
		worker_pool.worker_list = worker;
	} else {
		worker->next = worker_pool.worker_list;
		worker_pool.worker_list = worker;
	}
}

struct fs_monitor_worker * get_worker_list(void) {
	return worker_pool.worker_list;
}
