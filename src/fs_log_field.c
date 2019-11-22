/*
 * fs_log_field.c
 *
 *  Created on: Nov 19, 2019
 *      Author: gilbert
 */

#include "fs_log_field.h"
#include "fs_access_agent_consts.h"

#include <string.h>

void get_forward_ip(struct field_linked_list * header , char * field_value) {
	struct field_linked_list * ptr = header;
	while (ptr != 0) {
		if (ptr->index == FS_FIELD_DEFINE_FORWARD_IP) {
			strcpy(field_value , ptr->field);

			return;
		}

		ptr = ptr->next;
	}
}

void get_client_ip(struct field_linked_list * header , char * field_value) {
	struct field_linked_list * ptr = header;
	while (ptr != 0) {
		if (ptr->index == FS_FIELD_DEFINE_CLIENT_IP) {
			strcpy(field_value , ptr->field);

			return;
		}

		ptr = ptr->next;
	}
}

void get_method(struct field_linked_list * header , char * field_value) {
	struct field_linked_list * ptr = header;
	while (ptr != 0) {
		if (ptr->index == FS_FIELD_DEFINE_METHOD) {
			strcpy(field_value , ptr->field);

			return;
		}

		ptr = ptr->next;
	}
}

void get_status(struct field_linked_list * header , char * field_value) {
	struct field_linked_list * ptr = header;
	while (ptr != 0) {
		if (ptr->index == FS_FIELD_DEFINE_STATUS) {
			strcpy(field_value , ptr->field);

			return;
		}

		ptr = ptr->next;
	}
}

void get_timestamp(struct field_linked_list * header , char * field_value) {
	struct field_linked_list * ptr = header;
	while (ptr != 0) {
		if (ptr->index == FS_FIELD_DEFINE_TIME) {
			strcpy(field_value , ptr->field);

			return;
		}

		ptr = ptr->next;
	}
}

void get_resp_time(struct field_linked_list * header , char * field_value) {
	struct field_linked_list * ptr = header;
	while (ptr != 0) {
		if (ptr->index == FS_FIELD_DEFINE_RESP_TIME) {
			strcpy(field_value , ptr->field);

			return;
		}

		ptr = ptr->next;
	}
}

void get_interface(struct field_linked_list * header , char * field_value) {
	struct field_linked_list * ptr = header;
	while (ptr != 0) {
		if (ptr->index == FS_FIELD_DEFINE_INTERFACE) {
			strcpy(field_value , ptr->field);

			return;
		}

		ptr = ptr->next;
	}
}

void get_service_host(struct field_linked_list * header , char * field_value) {
	struct field_linked_list * ptr = header;
	while (ptr != 0) {
		if (ptr->index == FS_FIELD_DEFINE_SERVICE_HOST) {
			strcpy(field_value , ptr->field);

			return;
		}

		ptr = ptr->next;
	}
}
