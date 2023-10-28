.POSIX:

BUILD = CC=clang go build
BUILD_GNU = CC=musl-clang go build
BUILD_FLAGS = -buildvcs=false -x -o
BIN_PATH = /usr/local/bin/
BIN_NAME = patchouli

BATT_SRC = ./pkg/battery
C_BATT = battery.c
C_BATT_SRC = $(BATT_SRC)/$(C_BATT)

NET_SRC = ./pkg/network
C_NET = network.c
C_NET_SRC = $(NET_SRC)/$(C_NET)

freebsd:
	@cp $(BATT_SRC)/freebsd/$(C_BATT) $(C_BATT_SRC)
	@cp $(NET_SRC)/bsd/$(C_NET) $(C_NET_SRC)
	@cp $(NET_SRC)/bsd/bsd.h $(NET_SRC)/bsd.h

linux:
	@cp $(BATT_SRC)/linux/$(C_BATT) $(C_BATT_SRC)
	@cp $(BATT_SRC)/linux/linux.h $(BATT_SRC)/linux.h
	@cp $(NET_SRC)/linux/$(C_NET) $(C_NET_SRC)
	@cp $(NET_SRC)/linux/linux.h $(NET_SRC)/linux.h

netbsd:
	@cp $(BATT_SRC)/netbsd/$(C_BATT) $(C_BATT_SRC)
	@cp $(BATT_SRC)/netbsd/netbsd.h $(BATT_SRC)/netbsd.h
	@cp $(NET_SRC)/bsd/$(C_NET) $(C_NET_SRC)
	@cp $(NET_SRC)/bsd/bsd.h $(NET_SRC)/bsd.h

openbsd:
	@cp $(BATT_SRC)/openbsd/$(C_BATT) $(C_BATT_SRC)
	@cp $(BATT_SRC)/openbsd/openbsd.h $(BATT_SRC)/openbsd.h
	@cp $(NET_SRC)/bsd/$(C_NET) $(C_NET_SRC)
	@cp $(NET_SRC)/bsd/bsd.h $(NET_SRC)/bsd.h

install:
	@$(BUILD) $(BUILD_FLAGS) $(BIN_PATH)$(BIN_NAME)
	@printf "%s was installed to %s, please ensure that %s is in your PATH variable.\n" "$(BIN_NAME)" "$(BIN_PATH)" "$(BIN_PATH)"

install-gnu:
	@$(BUILD_GNU) $(BUILD_FLAGS) $(BIN_PATH)$(BIN_NAME)
	@printf "%s was installed to %s, please ensure that %s is in your PATH variable.\n" "$(BIN_NAME)" "$(BIN_PATH)" "$(BIN_PATH)"

clean:
	@rm -f $(C_BATT_SRC) $(BATT_SRC)/linux.h $(BATT_SRC)/netbsd.h $(BATT_SRC)/openbsd.h
	@rm -f $(C_NET_SRC) $(NET_SRC)/linux.h $(NET_SRC)/bsd.h

remove:
	rm $(BIN_PATH)$(BIN_NAME)
