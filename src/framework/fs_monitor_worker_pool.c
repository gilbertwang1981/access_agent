/*
 * fs_monitor_worker_pool.c
 *
 *  Created on: Nov 22, 2019
 *      Author: gilbert
 */


#include "fs_monitor_worker_pool.h"
#include "fs_monitor_log.h"
#include "fs_monitor_cfg.h"
#include "fs_monitor_connector_cfg.h"

#include <string.h>
#include <stdio.h>
#include <dlfcn.h>

static struct fs_monitor_worker_pool worker_pool;

struct fs_monitor_worker_pool * get_worker_pool() {
	return &worker_pool;
}

int init_worker_pool(char * pool_name , int pool_max_size , long separator , struct fs_monitor_common_cfg * common_cfg) {
	worker_pool.pool_max_size = pool_max_size;

	(void)strcpy(worker_pool.pool_name , pool_name);

	worker_pool.worker_list = 0;
	worker_pool.field_cfg_list = 0;
	worker_pool.dir_file_cfg_list = 0;

	worker_pool.dir_file_cfg_list = convert_dir_file_cfg(common_cfg);
	worker_pool.field_cfg_list = convert_field_cfg(common_cfg);
	worker_pool.filter_cfg_list = convert_filter_cfg(common_cfg);
	worker_pool.connector_cfg = convert_connector_cfg(common_cfg);

	void * handle_func = dlopen(worker_pool.connector_cfg->connector , RTLD_NOW);
	if (handle_func == 0) {
		dlerror();
		ERROR_LOG("初始化动态链接库失败,%s" , worker_pool.connector_cfg->connector);

		return -1;
	}

	worker_pool.connector_callback_func = (int (*)(char * , int , char *))dlsym(handle_func , "connnect_to_source");
	if (worker_pool.connector_callback_func == 0) {
		dlerror();
		ERROR_LOG("初始化动态链接库方法失败");

		return -1;
	}

	struct fs_monitor_dir_file_cfg * cfg_ptr = worker_pool.dir_file_cfg_list;
	while (cfg_ptr != 0) {
		struct fs_monitor_worker * worker = 0;
		if (0 == (worker = create_worker(cfg_ptr->dir , cfg_ptr->file , separator))) {
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
