##
## Main Makefile of the project
##

# Lib Dirs
IMGUI_DIR	=	lib/imgui
# Project name
NAME		=	dnd
# Compiler
CC			=	g++
# Flags
LIBS		=	`sdl2-config --libs`
CFLAGS		=	-W -Wall -Wextra -std=c++11 -g3
CFLAGS		+=	-I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
CFLAGS		+=	`sdl2-config --cflags`

# Sources
SRC			=	src/main.cpp					\
			src/Graphic/Menus/MainMenu.cpp		\
			src/Graphic/Widget/PlayerWidget.cpp	\

SRC			+= $(IMGUI_DIR)/imgui.cpp 							\
			$(IMGUI_DIR)/imgui_demo.cpp 						\
			$(IMGUI_DIR)/imgui_draw.cpp 						\
			$(IMGUI_DIR)/imgui_tables.cpp 						\
			$(IMGUI_DIR)/imgui_widgets.cpp						\
			$(IMGUI_DIR)/backends/imgui_impl_sdl2.cpp			\
			$(IMGUI_DIR)/backends/imgui_impl_sdlrenderer2.cpp	\

OBJ			=	$(SRC:.cpp=.o)

# By default compile everything
all: $(NAME)

# clean the project
clean:
	$(RM) $(OBJ)

# clean the project and the executable
fclean: clean
	$(RM) $(NAME)

# clean the project and the executable and recompile
re: fclean all

# Compile the project
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(IMGUI_HEADERS) $(OBJ) -o $(NAME)

# Compile the objects
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
