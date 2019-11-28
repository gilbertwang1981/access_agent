/*
 * fs_monitor_worker_pool.h
 *
 *  Created on: Nov 22, 2019
 *      Author: gilbert
 */

#ifndef _FS_MONITOR_WORKER_POOL_H_
#define _FS_MONITOR_WORKER_POOL_H_

#include "fs_access_agent_consts.h"
#include "fs_monitor_worker.h"
#include "fs_monitor_dir_file_cfg.h"
#include "fs_monitor_field_cfg.h"

struct fs_monitor_worker_pool {
	char pool_name[DEFAULT_STR_LEN];
	int pool_max_size;
	struct fs_monitor_worker * worker_list;
	struct fs_monitor_dir_file_cfg * dir_file_cfg_list;
	struct fs_monitor_field_cfg * field_cfg_list;
};

int init_worker_pool(char * pool_name , int pool_max_size , long separator , struct fs_monitor_common_cfg * common_cfg);
void add_worker_to_pool(struct fs_monitor_worker * worker);
struct fs_monitor_worker * get_worker_list(void);
struct fs_monitor_worker_pool * get_worker_pool(void);

#endif /* _FS_MONITOR_WORKER_POOL_H_ */
