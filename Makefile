BIN=bin
SRC=src
FLAGS=-Wall -Wextra -Werror
CMD_CONTROL=command_and_control
PORT_SCANNER=port_scanner


setup:
	mkdir -p $(BIN)/$(PORT_SCANNER)
	mkdir -p $(BIN)/$(CMD_CONTROL)
	make all

all:
	make $(BIN)/$(CMD_CONTROL)/reverse_shell


$(BIN)/$(CMD_CONTROL)/reverse_shell:$(SRC)/$(CMD_CONTROL)/reverse_shell.c
	gcc $(FLAGS) $< -o $@

$(BIN)/$PORT_SCANNER)/port_scanner:$(SRC)/$(PORT_SCANNER)/port_scanner.c
	gcc $(FLAGS) $< -o $@
