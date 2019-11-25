OBJS := fs_monitor.o main.o fs_monitor_callback.o \
	fs_file_analysis.o fs_field_linked_list.o \
	fs_udp.o fs_init_daemon.o fs_monitor_worker.o fs_monitor_worker_pool.o \
	fs_monitor_dir_file_cfg.o fs_monitor_field_cfg.o

LIBS := -L./

INCS := -I./

LDS := 

GCC := gcc

BIN := access_agent

${BIN}: ${OBJS}
	$(GCC) -o $@ $^ $(LIBS) $(LDS)
	@(echo "构建完成")

.PHONY: 
clean:
	$(RM) -rf *.o
	$(RM) -rf $(LIB)
	$(RM) -rf $(BIN)

%.o: %.c
	$(GCC) -fPIC -c -g -o $@ $< $(INCS)