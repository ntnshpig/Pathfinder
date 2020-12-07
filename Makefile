NAME	=	pathfinder

FLAG	=	-std=c11 -Wall -Wextra -Werror -Wpedantic

SRCD	=	src
INCD	=	inc
OBJD	=	obj

LMXA	:=	libmx/libmx.a
LMXI	:=	libmx/inc

INC		=	pathfinder.h
INCS	=	$(addprefix $(INCD)/, $(INC))

SRC		= 	main.c check.c parse_file.c pathfinder.c get_index_in_strarr.c delete_duplicate.c

SRCS	=	$(addprefix $(SRCD)/, $(SRC))
OBJS	=	$(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: install

install: $(LMXA) $(NAME)

$(NAME): $(OBJS)
	@clang $(FLAG) $(OBJS) $(LMXA) -o $@

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@clang $(FLAG) -c $< -o $@ -I$(INCD) -I$(LMXI)

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

$(LMXA):
	@make -sC libmx

clean:
	@make -sC libmx $@
	@rm -rf $(OBJD)

uninstall: clean
	@make -sC libmx $@
	@rm -rf $(NAME)

reinstall: uninstall install
