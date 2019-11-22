/*
 * fs_init_daemon.c
 *
 *  Created on: Nov 20, 2019
 *      Author: gilbert
 */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

void init_daemon() {
	int pid = -1;
	int i = -1;

	pid = fork();
	if(pid < 0) {
		(void)exit(1);
	} else if(pid>0) {
		(void)exit(0);
	}

	setsid();

	pid = fork();
	if( pid > 0) {
		(void)exit(0);
	} else if(pid < 0) {
		(void)exit(1);
	}

	for(i = 0;i < NOFILE;i ++) {
		(void)close(i);
	}

	return;
}
