/*
 * fs_monitor.h
 *
 *  Created on: Nov 19, 2019
 *      Author: gilbert
 */

#ifndef _FS_MONITOR_H_
#define _FS_MONITOR_H_

#include "fs_monitor_worker_pool.h"

void fs_changed_monitor(struct fs_monitor_worker_pool * worker_pool);

#endif /* _FS_MONITOR_H_ */
