##
## Makefile for bomberman in /home/bevill_a/rendu/cpp_bomberman
##
## Made by Alexis Bevillard
## Login   <bevill_a@epitech.net>
##
## Started on  Sat May 23 16:26:52 2015 Alexis Bevillard
## Last update Fri Jun 12 11:20:48 2015 Alexis Bevillard
##

NAME =		bomberman

SRC_DIR =	sources/
OBJ_DIR =	objects/
INC_DIR =	include/

LIB_DIR =	lib/libs/
LIB_INC_DIR =	lib/includes/

AUDIO_LIB =	SFML_Audio/lib
AUDIO_INC =	SFML_Audio/include

SRCS =		$(SRC_DIR)main.cpp \
		$(SRC_DIR)GameEngine.cpp \
		$(SRC_DIR)AObject.cpp \
		$(SRC_DIR)Marvin.cpp \
		$(SRC_DIR)Cube.cpp \
		$(SRC_DIR)Map.cpp \
		$(SRC_DIR)Menu.cpp \
		$(SRC_DIR)Pause.cpp \
		$(SRC_DIR)Bomb.cpp \
		$(SRC_DIR)Intro.cpp

OBJS =		$(patsubst $(SRC_DIR)%, $(OBJ_DIR)%, $(SRCS:.cpp=.o))

CPPFLAGS +=	-Wall -Wextra -Werror -std=c++11
CPPFLAGS +=	-I$(INC_DIR)
CPPFLAGS +=	-I$(LIB_INC_DIR)
CPPFLAGS +=	-I$(AUDIO_INC)

LDFLAGS +=	-L$(LIB_DIR) -lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -lpthread
LDFLAGS +=	-L$(AUDIO_LIB) -lsfml-audio -lsfml-system
LDFLAGS +=	-Wl,-rpath=$(LIB_DIR):$(AUDIO_LIB)

CPP_COMPILE =	g++ -c
CPP_LINK =	g++ -o
MKDIR =		mkdir -p
RM =		rm -rfv
ECHO_GREEN =	echo -e "\033[32m"
END_OF_ECHO =	"\033[0m"

all:		$(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
		@$(MKDIR) $(OBJ_DIR)
		@$(CPP_COMPILE) $< $(CPPFLAGS) -o $@
		@echo $(patsubst $(SRC_DIR)%, %, $<) compiled

$(NAME):	$(OBJS)
		@$(CPP_LINK) $(NAME) $(OBJS) $(LDFLAGS)
		@$(ECHO_GREEN)[OK] $(NAME) linked $(END_OF_ECHO)

clean:
		@$(RM) $(OBJ_DIR)
		@$(ECHO_GREEN)[OK] Every objects have been removed $(END_OF_ECHO)

fclean:		clean
		@$(RM) $(NAME)
		@$(ECHO_GREEN)[OK] $(NAME) removed $(END_OF_ECHO)

re:		fclean all

.PHONY:		all clean fclean re
