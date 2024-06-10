##
## EPITECH PROJECT, 2023
## client
## File description:
## network
##

SRC		=   src/Traductor.cpp			\
			src/TraductorElement.cpp	\
			src/TraductorError.cpp		\

OBJ 	= 	$(patsubst src/%.cpp,object/%.o,$(SRC))

NAME	=	traductor

FLAGS	=	-Wall 	\
			-Wextra	\
			-I./include

COMP	=	g++

$(NAME):	$(OBJ)
	ar rc lib$(NAME).a $(OBJ)

all:	$(NAME)

clean:
	@rm -rf $(OBJ)
	@rm -rf object

fclean: clean
	@rm -rf lib$(NAME).a

re: fclean all

object/%.o: src/%.cpp
	@mkdir -p $(@D)
	@$(COMP) $(FLAGS) -c -o $@ $<

test: all
	g++ -o test main.cpp $(FLAGS) -L./ -l$(NAME)
