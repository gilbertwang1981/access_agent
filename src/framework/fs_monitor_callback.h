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
void synchronize(struct fs_monitor_worker * worker , char * line , long separator);
void do_execute_connector(struct fs_monitor_worker * worker , struct field_linked_list * result);
int is_should_read(struct fs_monitor_worker * worker);
int is_filter_success(char * field_key , char * field_value);

#endif /* _FS_MONITOR_CALLBACK_H_ */
