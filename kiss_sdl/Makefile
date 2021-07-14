NAME = libkisssdl.a

CFILES = kiss_draw.c \
		kiss_general.c \
		kiss_posix.c \
		kiss_widgets.c 

OFILES	= $(CFILES:%.c=%.o)

LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
CFLAGS = -Wall -c -std=c89

### Linux

LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
CFLAGS = -Wall -c -std=c89


all: $(NAME)

%.o: %.c
	@gcc $(INCLUDE) -o $@ -c $<

$(NAME): $(OFILES)
	@ar rcs $(NAME) $(OFILES)

clean:
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all
