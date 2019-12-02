/*
 * fs_monitor_util.c
 *
 *  Created on: Nov 28, 2019
 *      Author: gilbert
 */

#include "fs_monitor_util.h"

#include <sys/stat.h>

int get_file_size(char * file_path) {
	struct stat statbuf;

	if (stat(file_path , &statbuf) == -1) {
		return 0;
	}

	return statbuf.st_size;
}
