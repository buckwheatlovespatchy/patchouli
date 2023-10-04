.POSIX:

BUILD = go build
BUILD_FLAGS = -buildvcs=false -x -o
BIN_PATH = /usr/local/bin/
BIN_NAME = patchouli
C_SRC = ./pkg/battery

netbsd:
	@cp $(C_SRC)/netbsd/netbsd-battery.c $(C_SRC)/battery.c
	@cp $(C_SRC)/netbsd/netbsd-battery.h $(C_SRC)/battery.h
	@$(BUILD) $(BUILD_FLAGS) $(BIN_PATH)$(BIN_NAME)
	@printf "%s was installed to %s, please ensure that %s is in your PATH variable.\n" "$(BIN_NAME)" "$(BIN_PATH)" "$(BIN_PATH)"

openbsd:
	@cp $(C_SRC)/openbsd/openbsd-battery.c $(C_SRC)/battery.c
	@cp $(C_SRC)/openbsd/openbsd-battery.h $(C_SRC)/battery.h
	@$(BUILD) $(BUILD_FLAGS) $(BIN_PATH)$(BIN_NAME)
	@printf "%s was installed to %s, please ensure that %s is in your PATH variable.\n" "$(BIN_NAME)" "$(BIN_PATH)" "$(BIN_PATH)"

clean:
	rm $(C_SRC)/battery.c $(C_SRC)/battery.h

remove:
	rm $(BIN_PATH)$(BIN_NAME)
