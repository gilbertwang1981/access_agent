TARGETS := FWK_TARGET CONNECTOR_TARGET
TARGETS_CLEAN := FWK_CLEAN_TARGET CONNECTOR_CLEAN_TARGET

FWK_TARGET:
	@(cd framework && $(MAKE)) || exit 1;

CONNECTOR_TARGET:
	@(cd connector && $(MAKE) all) || exit 1;
	
FWK_CLEAN_TARGET:
	@(cd framework && $(MAKE) clean) || exit 1;

CONNECTOR_CLEAN_TARGET:
	@(cd connector && $(MAKE) clean) || exit 1;
 
all: $(TARGETS)

clean: $(TARGETS_CLEAN)