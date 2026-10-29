# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgervet <42@leogervet.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/07 14:34:30 by lgervet           #+#    #+#              #
#    Updated: 2026/02/05 12:59:23 by lgervet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compile & flags
CC 			:= cc
CFLAGS		:= -g3 -Wall -Wextra -Werror
CPPFLAGS	:= -I .

# Commands
AR			:= ar
ARFLAGS		:= rcs
RM			:= rm -f

NAME		:= libft.a

# Files
SRCS 		:= \
	srcs/libc/ft_atoi.c \
	srcs/libc/ft_atol.c \
	srcs/libc/ft_bzero.c \
	srcs/libc/ft_calloc.c \
	srcs/libc/ft_isalnum.c \
	srcs/libc/ft_isalpha.c \
	srcs/libc/ft_isascii.c \
	srcs/libc/ft_isdigit.c \
	srcs/libc/ft_isprint.c \
	srcs/libc/ft_itoa.c \
	srcs/libc/ft_memchr.c \
	srcs/libc/ft_memcmp.c \
	srcs/libc/ft_memcpy.c \
	srcs/libc/ft_memmove.c \
	srcs/libc/ft_memset.c \
	srcs/libc/ft_putchar_fd.c \
	srcs/libc/ft_putendl_fd.c \
	srcs/libc/ft_putnbr_fd.c \
	srcs/libc/ft_putstr_fd.c \
	srcs/libc/ft_split.c \
	srcs/libc/ft_strchr.c \
	srcs/libc/ft_strdup.c \
	srcs/libc/ft_striteri.c \
	srcs/libc/ft_strjoin.c \
	srcs/libc/ft_strlcat.c \
	srcs/libc/ft_strlcpy.c \
	srcs/libc/ft_strlen.c \
	srcs/libc/ft_strmapi.c \
	srcs/libc/ft_strncmp.c \
	srcs/libc/ft_strnstr.c \
	srcs/libc/ft_strrchr.c \
	srcs/libc/ft_strtrim.c \
	srcs/libc/ft_substr.c \
	srcs/libc/ft_tolower.c \
	srcs/getnextline/get_next_line.c \
	srcs/getnextline/ft_realloc.c \
	srcs/libc/ft_toupper.c \
	srcs/printf/dispatch.c \
	srcs/printf/ft_printf.c \
	srcs/printf/numbers.c \
	srcs/printf/strings.c \
	srcs/printf/write_basics.c \

BONUS_SRCS	:= \
	srcs/libc/ft_lstadd_back_bonus.c \
	srcs/libc/ft_lstadd_front_bonus.c \
	srcs/libc/ft_lstclear_bonus.c \
	srcs/libc/ft_lstdelone_bonus.c \
	srcs/libc/ft_lstiter_bonus.c \
	srcs/libc/ft_lstlast_bonus.c \
	srcs/libc/ft_lstmap_bonus.c \
	srcs/libc/ft_lstnew_bonus.c \
	srcs/libc/ft_lstsize_bonus.c
OBJS		:= $(SRCS:.c=.o)
BONUS_OBJS	:= $(BONUS_SRCS:.c=.o)
BONUS_FLAG	:= .bonus

.PHONY: all clean fclean re bonus

# Mandatory main rule
all: $(NAME)

# Lib creation
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# clean, fclean, re, bonus rules
clean:
	$(RM) $(OBJS)
	$(RM) $(BONUS_OBJS)
	$(RM) $(BONUS_FLAG)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean 
	$(MAKE) all

# bonus:
bonus: $(BONUS_FLAG)

$(BONUS_FLAG): $(NAME) $(BONUS_OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(BONUS_OBJS)
	touch $(BONUS_FLAG)
