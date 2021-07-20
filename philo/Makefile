NAME	= philo

SRCS	= ./philosophers.c ./utils.c ./status_philo.c ./fork_mutex.c ./create_philo.c ./loop_philo.c ./threads_process.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -g3 -fsanitize=address

LIBS	= -pthread

${NAME}:	${OBJS}
			@echo "\033[36mCompiled..."
			@${CC} ${CFLAGS} ${LIBS} ${OBJS} -o ${NAME}
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
