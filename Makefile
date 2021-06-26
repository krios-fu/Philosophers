NAME	= philo

SRCS	= ./philosophers.c ./utils.c

OBJS	= ${SRCS:.c=.o}

GCC		= gcc

FLAGS	= -Wall -Werror -Wextra -I

LIBS	= -pthread

${NAME}:	${OBJS}
			@echo "\033[36mCompiled..."
			@${GCC} ${FLAGS} ${LIBS} ${OBJS} -o ${NAME}
			@sleep 3
			@clear
			@echo "\033[1;36m2b || !2be // that is the question...\033[0m\n"

all:	${NAME}

clean:
		@${RM} ${OBJS}
		@echo "\033[1;31mDeleted file" ${OBJS}

fclean:		clean
			@${RM} ${NAME}
			@echo "\033[1;31mDeleted program"  ${NAME}

re: fclean all

.PHONY: all clean re 
