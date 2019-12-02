OBJS := udp_connector.o

LIBS := -L./

INCS := -I./

LDS := 

GCC := gcc

TARGET := udp_connector.so

${TARGET}: ${OBJS}
	$(GCC) -shared -o $@ $^ $(LIBS) $(LDS)
	@(echo "构建完成")

.PHONY: 
clean:
	$(RM) -rf *.o
	$(RM) -rf $(LIB)
	$(RM) -rf $(TARGET)

%.o: %.c
	$(GCC) -fPIC -c -g -o $@ $< $(INCS)