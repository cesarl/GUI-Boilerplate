NAME		=	exec

CC		=	g++

RM		=	rm -f

CPPFLAGS	=	-W -Wextra -Wall -Werror

CPPFLAGS	+=	-Icomponents -Iscenes -Imanagers -Iheaders -Igui -I.

LDFLAGS		=	-L/usr/lib -lallegro -lallegro_dialog -lallegro_primitives -lallegro_ttf -lallegro_font -lallegro_image

INC		=	-I/usr/include/allegro5

SRCS		=	MainManager.cpp \
			ImageManager.cpp \
			EventManager.cpp \
			SceneManager.cpp \
			FontManager.cpp \
			ScoreManager.cpp \
			Option.cpp \
			AScene.cpp \
			Vector3d.cpp \
			gui/GuiComponent.cpp \
			gui/GuiNumber.cpp \
			gui/GuiRangeNumber.cpp \
			gui/GuiSelectableGroup.cpp \
			gui/GuiSelectable.cpp \
			gui/GuiSelectableNumber.cpp \
			gui/GuiSelectableText.cpp \
			gui/GuiText.cpp \
			scenes/SceneMenu.cpp \
			scenes/MainMenu.cpp \
			scenes/NewGameMenu.cpp \
			scenes/ScoreMenu.cpp \
			main.cpp

OBJS		=	$(SRCS:.cpp=.o)

ECHO		=	echo -e

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			@$(CC) $(OBJS) -o $(NAME) $(INC) $(LDFLAGS)
			@$(ECHO) '\033[1;37;44m> Compiled {\033[4m$(NAME)}\033[0m'

clean		:
			@$(RM) $(OBJS)
			@$(ECHO) '\033[1;37;41m> Directory cleaned\033[0m'

fclean		:	clean
			@$(RM) $(NAME)
			@$(ECHO) '\033[1;37;41m> Remove executable\033[0m'

re		:	fclean all

.PHONY		:	all clean re
