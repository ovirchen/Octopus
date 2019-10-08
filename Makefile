
NAME = Octopus

SOURCES = source/main.cpp source/Game.cpp source/Octopus.cpp source/Animation.cpp

OBJECTS = $(SOURCES:.cpp=.o)

FLAGS = -framework OpenGL -framework AppKit -std=c++14

INCLUDES = 		-I include/ \
                -I frameworks/SDL2.framework/Versions/A/Headers \
				-I frameworks/SDL2_image.framework/Versions/A/Headers \
				-F ./frameworks

FRAMEWORKS	=	-F ./frameworks \
				-rpath @loader_path/frameworks \
				-framework SDL2 -framework SDL2_image

HEADERS = include/*.h

all: $(NAME)

%.o : %.cpp
	@g++ $(FLAGS) -I. $(FLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJECTS) $(HEADERS)
	@g++ $(FLAGS) $(FRAMEWORKS) -o $@ -I. $(OBJECTS)
	@echo "\033[1;32mOctopus is ready\033[0m"

clean:
	@rm -f source/*.o
	@echo "\033[1;32mObject files were removed\033[0m"

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re
