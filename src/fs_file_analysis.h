/*
 * fs_file_analysis.h
 *
 *  Created on: Nov 19, 2019
 *      Author: gilbert
 */

#ifndef _FS_FILE_ANALYSIS_H_
#define _FS_FILE_ANALYSIS_H_

#include "fs_filed_linked_list.h"

int open_file(char * path , unsigned int offset);

int close_file(int fd);

char * read_line(int fd , char * line);

struct field_linked_list * analysis_line(char * line);

#endif /* _FS_FILE_ANALYSIS_H_ */
