BIN=bin
SRC=src
FLAGS=-Wall -Wextra -Werror


$(BIN)/reverse_shell:$(SRC)/reverse_shell.c
	gcc $(FLAGS) $< -o $@

$(BIN)/port_scanner:$(SRC)/port_scanner.c
	gcc $(FLAGS) $< -o $@
