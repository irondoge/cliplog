CC :=		gcc
CFLAGS :=	-W -Wall -Wextra -pedantic -std=c99 \
			$(shell pkg-config --cflags gdk-3.0 gtk+-3.0)

LD :=		$(CC)
LDFLAGS :=	$(shell pkg-config --libs gdk-3.0 gtk+-3.0)

NAME :=		cliplog
SRC :=		main.c
OBJ :=		$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(LD) -o $@ $< $(LDFLAGS) $(LDLIBS)

%.o:		%.c
			$(CC) -c $(CFLAGS) $^ -o $@

RM :=		@$(RM) -v

mostlyclean:; $(RM) $(OBJ)

clean:		mostlyclean
			$(RM) $(NAME)

distclean:	clean

re:			mostlyclean all

.PHONY:		all mostlyclean clean distclean re