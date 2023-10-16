.POSIX:

BUILD = CC=clang go build
BUILD_FLAGS = -buildvcs=false -x -o
BIN_PATH = /usr/local/bin/
BIN_NAME = patchouli

BATT_SRC = ./pkg/battery
C_BATT = battery.c
H_BATT = battery.h
C_BATT_SRC = $(BATT_SRC)/$(C_BATT)
H_BATT_SRC = $(BATT_SRC)/$(H_BATT)

NET_SRC = ./pkg/network
C_NET = network.c
H_NET = network.h
C_NET_SRC = $(NET_SRC)/$(C_NET)
H_NET_SRC = $(NET_SRC)/$(H_NET)

freebsd:
	@cp $(BATT_SRC)/freebsd/$(C_BATT) $(C_BATT_SRC)
	@cp $(BATT_SRC)/freebsd/$(H_BATT) $(H_BATT_SRC)
	@cp $(NET_SRC)/bsd/$(C_NET) $(C_NET_SRC)
	@cp $(NET_SRC)/bsd/$(H_NET) $(H_NET_SRC)

linux:
	@cp $(BATT_SRC)/linux/$(C_BATT) $(C_BATT_SRC)
	@cp $(BATT_SRC)/linux/$(H_BATT) $(H_BATT_SRC)
	@cp $(NET_SRC)/linux/$(C_NET) $(C_NET_SRC)
	@cp $(NET_SRC)/linux/$(H_NET) $(H_NET_SRC)

netbsd:
	@cp $(BATT_SRC)/netbsd/$(C_BATT) $(C_BATT_SRC)
	@cp $(BATT_SRC)/netbsd/$(H_BATT) $(H_BATT_SRC)
	@cp $(NET_SRC)/bsd/$(C_NET) $(C_NET_SRC)
	@cp $(NET_SRC)/bsd/$(H_NET) $(H_NET_SRC)

openbsd:
	@cp $(BATT_SRC)/openbsd/$(C_BATT) $(C_BATT_SRC)
	@cp $(BATT_SRC)/openbsd/$(H_BATT) $(H_BATT_SRC)
	@cp $(NET_SRC)/bsd/$(C_NET) $(C_NET_SRC)
	@cp $(NET_SRC)/bsd/$(H_NET) $(H_NET_SRC)

install:
	@$(BUILD) $(BUILD_FLAGS) $(BIN_PATH)$(BIN_NAME)
	@printf "%s was installed to %s, please ensure that %s is in your PATH variable.\n" "$(BIN_NAME)" "$(BIN_PATH)" "$(BIN_PATH)"

clean:
	rm $(C_BATT_SRC) $(H_BATT_SRC) $(C_NET_SRC) $(H_NET_SRC)

remove:
	rm $(BIN_PATH)$(BIN_NAME)
