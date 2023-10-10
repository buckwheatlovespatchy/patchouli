.POSIX:

BUILD = CC=clang go build
BUILD_FLAGS = -buildvcs=false -x -o
BIN_PATH = /usr/local/bin/
BIN_NAME = patchouli

BATT_SRC = ./pkg/battery
C_BATT = $(BATT_SRC)/battery.c
H_BATT = $(BATT_SRC)/battery.h

freebsd:
	@cp $(BATT_SRC)/freebsd/freebsd-battery.c $(C_BATT)
	@cp $(BATT_SRC)/freebsd/freebsd-battery.h $(H_BATT)
	@$(BUILD) $(BUILD_FLAGS) $(BIN_PATH)$(BIN_NAME)
	@printf "%s was installed to %s, please ensure that %s is in your PATH variable.\n" "$(BIN_NAME)" "$(BIN_PATH)" "$(BIN_PATH)"	

netbsd:
	@cp $(BATT_SRC)/netbsd/netbsd-battery.c $(C_BATT)
	@cp $(BATT_SRC)/netbsd/netbsd-battery.h $(H_BATT)
	@$(BUILD) $(BUILD_FLAGS) $(BIN_PATH)$(BIN_NAME)
	@printf "%s was installed to %s, please ensure that %s is in your PATH variable.\n" "$(BIN_NAME)" "$(BIN_PATH)" "$(BIN_PATH)"

openbsd:
	@cp $(BATT_SRC)/openbsd/openbsd-battery.c $(C_BATT)
	@cp $(BATT_SRC)/openbsd/openbsd-battery.h $(H_BATT)
	@$(BUILD) $(BUILD_FLAGS) $(BIN_PATH)$(BIN_NAME)
	@printf "%s was installed to %s, please ensure that %s is in your PATH variable.\n" "$(BIN_NAME)" "$(BIN_PATH)" "$(BIN_PATH)"

clean:
	rm $(C_BATT) $(H_BATT)

remove:
	rm $(BIN_PATH)$(BIN_NAME)
