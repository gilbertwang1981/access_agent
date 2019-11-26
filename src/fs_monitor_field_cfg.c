/*
 * fs_monitor_field_cfg.c
 *
 *  Created on: Nov 25, 2019
 *      Author: gilbert
 */

#include "fs_monitor_field_cfg.h"
#include "fs_monitor_log.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

static struct fs_monitor_field_cfg * file_cfg = 0;

struct fs_monitor_field_cfg * read_field_cfg(char * cfg_path) {
	int fd = -1;
	if (-1 == (fd = open(cfg_path , O_RDWR | O_CREAT , 0755))) {
		ERROR_LOG("打开文件失败,%s" , cfg_path);

		return 0;
	}

	char line[DEFAULT_LINE_BUUFER_SIZE] = {0};
	while (read_line_without_null_field_cfg(fd , line) > 0) {
		if (strlen(line) > 0) {
			handle_field_cfg_line(line);
		}

		(void)memset(line , 0x00 , DEFAULT_LINE_BUUFER_SIZE);
	}

	(void)close(fd);

	if (file_cfg == 0) {
		return 0;
	}

	struct fs_monitor_field_cfg * ptr = file_cfg;
	struct fs_monitor_field_cfg * header = 0;
	while (ptr != 0) {
		if (header == 0) {
			header = ptr;
			ptr = ptr->next;
			header->next = 0;
		} else {
			struct fs_monitor_field_cfg * tmp = ptr;
			ptr = ptr->next;
			tmp->next = header;
			header = tmp;
		}
	}

	file_cfg = header;

	return file_cfg;
}

int read_line_without_null_field_cfg(int fd , char * line) {
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

	line[index] = '\0';

	return 0;
}

void handle_field_cfg_line(char * line) {
	char field[DEFAULT_STR_LEN] = {0};
	int size = -1;
	int index = -1;

	char * token = strtok(line , "=");
	if (token != 0) {
		(void)strcpy(field , token);
		token = strtok(0 , "=");
		if (token != 0) {
			char tmp_value[DEFAULT_STR_LEN] = {0};
			(void)strcpy(tmp_value , token);

			char * t = strtok(tmp_value , ":");
			if (t != 0) {
				index = atoi(t);

				t = strtok(0 , ":");
				if (t != 0) {
					size = atoi(t);
				}
			}
		}
	}

	if (size >= 0 && index >= 0) {
		struct fs_monitor_field_cfg * pfield_cfg = (struct fs_monitor_field_cfg *)malloc(sizeof(struct fs_monitor_field_cfg));
		pfield_cfg->index = index;
		pfield_cfg->size = size;
		(void)strcpy(pfield_cfg->field , field);
		pfield_cfg->next = 0;

		if (file_cfg == 0) {
			file_cfg = pfield_cfg;
		} else {
			pfield_cfg->next = file_cfg;
			file_cfg = pfield_cfg;
		}
	}
}

