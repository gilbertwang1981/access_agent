/*
 * fs_monitor_worker_pool.h
 *
 *  Created on: Nov 21, 2019
 *      Author: gilbert
 */

#ifndef _FS_MONITOR_WORKER_H_
#define _FS_MONITOR_WORKER_H_

#include "fs_access_agent_consts.h"

struct fs_monitor_worker {
	char dir[DEFAULT_STR_LEN];
	char file[DEFAULT_STR_LEN];
	unsigned int offset;
	int notify_fd;
	int watch_dog;
	long separator;
	int sampling_rate_ctr;

	struct fs_monitor_worker * next;
};

struct fs_monitor_worker * create_worker(char * dir , char * file , long separator);

#endif /* _FS_MONITOR_WORKER_H_ */
