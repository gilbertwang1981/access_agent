/*
 * fs_monitor_callback.h
 *
 *  Created on: Nov 19, 2019
 *      Author: gilbert
 */

#ifndef _FS_MONITOR_CALLBACK_H_
#define _FS_MONITOR_CALLBACK_H_

#include "fs_filed_linked_list.h"
#include "fs_monitor_worker.h"

void file_modified(struct fs_monitor_worker * worker);
void file_deleted(struct fs_monitor_worker * worker);
void file_created(struct fs_monitor_worker * worker);
void file_moved(struct fs_monitor_worker * worker);
void synchronize(struct fs_monitor_worker * worker , char * line);
void packet_udp(struct fs_monitor_worker * worker , struct field_linked_list * result);

#endif /* _FS_MONITOR_CALLBACK_H_ */
