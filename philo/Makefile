NAME = philo

FILES = philo \
		alloc \
		alloc_lst \
		checker \
		routine \
		times \
		tower_alloc \
		init \
		utils \
		error

SRCS = $(foreach f, $(FILES), sources/$(f).c)

OBJS = $(foreach f, $(FILES), objects/$(f).o)

#-------------------------------- compile
CC = cc
FLAGS = -Werror -Wextra -Wall -g3 -pthread
ADDRESS = -fsanitize=address
THREADS = -fsanitize=thread

FLAGS_ADDRESS = $(FLAGS) $(ADDRESS)
FLAGS_THREADS = $(FLAGS) $(THREADS)

#-------------------------------- clean
RM = rm -rf

#--------------------- ANSI color codes
RED = \033[31m
PINK = \033[35m
RESET = \033[0m

#----------------------- Default build
$(NAME): $(OBJS)
	@echo "🔨 Building $(PINK)$(NAME)$(RESET)..."
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "✅ Build completed: $(PINK)$(NAME)$(RESET)"

#--------- Build with AddressSanitizer
debug_address: fclean $(OBJS)
	@echo "🔍 Building $(PINK) $(NAME) $(RESET)with AddressSanitizer..."
	@$(CC) $(FLAGS_ADDRESS) $(OBJS) -o $(NAME)
	@echo "✅ AddressSanitizer build completed: $(PINK)$(NAME)$(RESET)"

#--------- Build with ThreadSanitizer
debug_thread: fclean $(OBJS)
	@echo "🔍 Building $(PINK)$(NAME) $(RESET)with ThreadSanitizer..."
	@$(CC) $(FLAGS_THREADS) $(OBJS) -o $(NAME)
	@echo "✅ ThreadSanitizer build completed: $(PINK)$(NAME)$(RESET)"

#--------------- Compile object files
objects/%.o: sources/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -o $@ -c $<

#--------------------- Clean commands
clean:
	@echo "🧹 $(RED)Removing object files...$(RESET)"
	@$(RM) $(OBJS)

fclean: clean
	@echo "🧹 $(RED)Removing executable...$(RESET)"
	@$(RM) $(NAME)

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re debug_address debug_thread
