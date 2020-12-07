SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(addprefix obj/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard inc/*.h)

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: LIBMX

LIBMX: $(OBJ_FILES)
	@ar rcs libmx.a $^
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"
$(OBJ_FILES): obj 
obj:
	@mkdir -p $@
obj/%.o: src/%.c $(INC_FILES)
	clang $(CFLAGS) -c $< -o $@ -I inc
	@printf "\r\33[2K$(NAME)\033[33;1m\t compile \033[0m$(<:src/%.c=%)\r"
clean:
	@rm -rf obj $@
	@rm -rf $(OBJ_FILES) $@	
	@printf "obj in $(NAME)\t \033[31;1mdeleted\033[0m\n"
uninstall: clean
	@rm -rf libmx.a
	@@printf "$(NAME)\t \033[31;1muninstalled\033[0m\n"
reinstall: uninstall all

.PHONY: all uninstall clean reinstall
