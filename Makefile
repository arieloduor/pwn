BIN=bin
SRC=src

$(BIN)/reverse_shell:$(SRC)/reverse_shell.c
	gcc $< -o $@

$(BIN)/port_scanner:$(SRC)/port_scanner.c
	gcc $< -o $@
