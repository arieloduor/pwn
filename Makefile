BIN=bin
SRC=src
FLAGS=-Wall -Wextra -Werror
REVERSE_SHELL=reverse_shell
TCP_CONNECT_SCAN=tcp_connect_scan
FLAGS=

setup:
	mkdir -p $(BIN)/$(TCP_CONNECT_SCAN)
	mkdir -p $(BIN)/$(REVERSE_SHELL)
	make all

all:
	make $(BIN)/$(REVERSE_SHELL)/reverse_shell


$(BIN)/$(REVERSE_SHELL)/reverse_shell:$(SRC)/$(REVERSE_SHELL)/reverse_shell.c
	gcc $(FLAGS) $< -o $@

$(BIN)/$(TCP_CONNECT_SCAN)/port_scanner:$(SRC)/$(TCP_CONNECT_SCAN)/port_scanner.c
	gcc $(FLAGS) $< -o $@
