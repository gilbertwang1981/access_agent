#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <sys/time.h>
#include <sys/select.h>

#include "fs_monitor.h"
#include "fs_monitor_callback.h"
#include "fs_access_agent_consts.h"
#include "fs_monitor_log.h"

void handle_event(struct fs_monitor_worker * worker) {
	char buffer[INOTIFY_BUFFER_SIZE] = {0};
	if (read(worker->notify_fd , buffer , sizeof(buffer)) > 0)  {
		int offset = 0;
		char * ptr = buffer;
		while (offset < INOTIFY_BUFFER_SIZE) {
			struct inotify_event * event = (struct inotify_event *)(ptr + offset);
			if (event->wd == worker->watch_dog) {
				if (event->mask & IN_MODIFY) {
					file_modified(worker);
				}

				if (event->mask & IN_CREATE) {
					file_created(worker);
				}

				if (event->mask & IN_DELETE) {
					file_deleted(worker);
				}

				if (event->mask & IN_MOVED_FROM) {
					file_moved(worker);
				}
			}

			offset += sizeof(struct inotify_event);
		}
	}

}

void fs_changed_monitor(struct fs_monitor_worker_pool * worker_pool) {
	struct timeval timeout;
	fd_set readfd;

	while (1) {
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		FD_ZERO(&readfd);
		struct fs_monitor_worker * pworker = worker_pool->worker_list;
		int max_fd = -1;
		while (pworker != 0) {
			FD_SET(pworker->notify_fd , &readfd);
			if (pworker->notify_fd > max_fd) {
				max_fd = pworker->notify_fd;
			}
			pworker = pworker->next;
		}

		int ret = select(max_fd + 1 , &readfd , 0 , 0 , &timeout);
		if (ret == -1) {
			ERROR_LOG("I/O多路复用错误");
		} else if (ret > 0) {
			struct fs_monitor_worker * pworker = worker_pool->worker_list;
			while (pworker != 0) {
				if(FD_ISSET(pworker->notify_fd , &readfd)) {
					handle_event(pworker);
				}
				pworker = pworker->next;
			}
		} else {
			continue;
		}
	}
}
