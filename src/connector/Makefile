TARGETS := STDOUT_CONNECTOR_TARGET UDP_CONNECTOR_TARGET

TARGETS_CLEAN := STDOUT_CONNECTOR_CLEAN_TARGET UDP_CONNECTOR_CLEAN_TARGET

STDOUT_CONNECTOR_TARGET:
	@(cd stdout_connector && $(MAKE)) || exit 1;
	
UDP_CONNECTOR_TARGET:
	@(cd udp_connector && $(MAKE)) || exit 1;
	
STDOUT_CONNECTOR_CLEAN_TARGET:
	@(cd stdout_connector && $(MAKE) clean) || exit 1;

UDP_CONNECTOR_CLEAN_TARGET:
	@(cd udp_connector && $(MAKE) clean) || exit 1;
 
all: $(TARGETS)

clean: $(TARGETS_CLEAN)