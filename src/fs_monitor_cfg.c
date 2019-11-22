/*
 * fs_monitor_cfg.c
 *
 *  Created on: Nov 22, 2019
 *      Author: gilbert
 */

#include "fs_monitor_cfg.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

static struct fs_monitor_cfg cfg[CFG_MAX_ITEM];

int read_line_without_null(int fd , char * line) {
	char c = 0x00;
	int index = 0;
	int line_counter = 0;
	while (1 == read(fd , &c , 1)) {
		line_counter ++;

		if (c == '\n') {
			line[index] = '\0';

			return line_counter;
		}

		line[index ++] = c;

		if (index == DEFAULT_LINE_BUUFER_SIZE - 1) {
			line[DEFAULT_LINE_BUUFER_SIZE - 1] = '\0';

			return line_counter;
		}
	}

	return 0;
}

void handle_cfg_line(struct fs_monitor_cfg * cfg , char * line) {
	char field[DEFAULT_STR_LEN] = {0};
	char value[DEFAULT_STR_LEN] = {0};
	char field_name[DEFAULT_STR_LEN] = {0};
	int field_index = -1;

	char * token = strtok(line , "=");
	if (token != 0) {
		(void)strcpy(field , token);

		token = strtok(0 , "=");
		if (token != 0) {
			(void)strcpy(value , token);
		}

		char * t = strtok(field , "_");
		if (t != 0) {
			(void)strcpy(field_name , t);

			t = strtok(0 , "_");
			if (t != 0) {
				field_index = atoi(t);
			}
		}
	}

	if (strcmp(field_name , CFG_FIELD_NAME_DIR) == 0) {
		(void)strcpy(cfg[field_index].dir , value);
	} else if (strcmp(field_name , CFG_FIELD_NAME_FILE) == 0) {
		(void)strcpy(cfg[field_index].file , value);
	} else if (strcmp(field_name , CFG_FIELD_NAME_HOST) == 0) {
		(void)strcpy(cfg[field_index].host , value);
	} else if (strcmp(field_name , CFG_FIELD_NAME_PORT) == 0) {
		cfg[field_index].port = atoi(value);
	}
}

struct fs_monitor_cfg * read_cfg(char * cfg_path) {
	int i =0;
	for (;i < CFG_MAX_ITEM; i ++) {
		(void)memset(cfg[i].dir , 0x00 , DEFAULT_STR_LEN);
		(void)memset(cfg[i].file , 0x00 , DEFAULT_STR_LEN);
		(void)memset(cfg[i].host , 0x00 , DEFAULT_STR_LEN);
		cfg[i].port = -1;
	}

	int fd = -1;
	if (-1 == (fd = open(cfg_path , O_RDWR | O_CREAT , 0755))) {
		perror("打开文件失败");

		return 0;
	}

	char line[DEFAULT_LINE_BUUFER_SIZE] = {0};
	while (read_line_without_null(fd , line) > 0) {
		if (strlen(line) > 0) {
			handle_cfg_line(cfg , line);
		}

		(void)memset(line , 0x00 , DEFAULT_LINE_BUUFER_SIZE);
	}

	(void)close(fd);

	struct fs_monitor_cfg * ret = 0;
	for (i = 0;i < CFG_MAX_ITEM; i ++) {
		if (strlen(cfg[i].dir) > 0) {
			struct fs_monitor_cfg * ptr = (struct fs_monitor_cfg *)malloc(sizeof(struct fs_monitor_cfg));
			(void)strcpy(ptr->dir , cfg[i].dir);
			(void)strcpy(ptr->file , cfg[i].file);
			(void)strcpy(ptr->host , cfg[i].host);
			ptr->port = cfg[i].port;

			ptr->next = 0;

			if (ret == 0) {
				ret = ptr;
			} else {
				ptr->next = ret;
				ret = ptr;
			}
		}
	}

	return ret;
}
