# Name of the binary
NAME = cub3D_web
SHELL := /bin/bash

# Compiler and flags
CC = emcc
CFLAGS = -Wall -Werror -Wextra -O3 -I./inc

# Emscripten-specific flags
WEBFLAGS = -s USE_GLFW=3 -s USE_WEBGL2=1 -s WASM=1 \
			-s ALLOW_MEMORY_GROWTH=1 -s NO_EXIT_RUNTIME=1 \
			--preload-file maps@/maps \
			--preload-file textures@/textures \
			-s EXPORTED_RUNTIME_METHODS='["requestFullscreen"]'

# Linker flags for emscripten (silence the warning and strip debug info)
LDFLAGS = -Wno-limited-postlink-optimizations -g0

LIBFT = ./libft/libft.a
MLX = ./MLX42/build/libmlx42.a
BINDIR = bin

# Source files (auto-discover recursively)
SRCS := $(shell find src -type f -name '*.c')

OBJS := $(patsubst %.c,$(BINDIR)/%.o,$(SRCS))


.SILENT:

# Default target
all: $(NAME).html

# Ensure both emcc and emcmake are available
check-emscripten:
	@command -v emcc >/dev/null 2>&1 || { echo "emcc not found"; exit 1; }
	@command -v emcmake >/dev/null 2>&1 || { echo "emcmake not found"; exit 1; }

# Ensure bin directory exists before building objects
$(BINDIR):
	@mkdir -p $(BINDIR) $(BINDIR)/src/parsing $(BINDIR)/src/execution

# Compile .c files into .o files with emcc
$(BINDIR)/%.o: %.c | $(BINDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Linking libft (reclone if missing, then build for emscripten)
$(LIBFT):
	@if [ ! -d "libft" ] || [ ! -f "libft/Makefile" ]; then \
		echo $(GREEN)"Cloning libft..."$(DEFAULT); \
		git clone https://github.com/ygalsk/libft.git libft; \
	fi
		echo $(GREEN)"Building libft for web..."$(DEFAULT); \
		$(MAKE) -s --no-print-directory -C libft fclean; \
		$(MAKE) -s --no-print-directory -C libft CC=$(CC) AR=emar RANLIB=emranlib; \

# MLX42 library for Emscripten (robust rebuild)
$(MLX):
	@echo $(GREEN)"Building MLX42 (web)..."$(DEFAULT)
	@if [ ! -d "MLX42" ]; then \
		git clone --depth=1 --branch v2.3.4 https://github.com/codam-coding-college/MLX42.git MLX42; \
	fi
	@cd MLX42 && emcmake cmake -B build -DDEBUG=1 >/dev/null 2>&1
	@cd MLX42 && cmake --build build -j >/dev/null 2>&1
	@[ -f "$(MLX)" ] || { echo $(RED)"Failed to build MLX42"$(DEFAULT); exit 1; }

# Build HTML and bust JS cache inside it
$(NAME).html: check-emscripten $(LIBFT) $(MLX) $(OBJS)
	@echo "Linking: $(NAME).html"
	@$(CC) $(WEBFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LIBFT) $(MLX)
	@v=$$(date +%s); sed -i "s#src=\"$(NAME).js\"#src=\"$(NAME).js?v=$$v\"#g" $(NAME).html || true

# Remove all object files
clean:
	@rm -rf $(BINDIR)
	@rm -f $(NAME).html $(NAME).js $(NAME).wasm $(NAME).data $(NAME)-*.html
# 	@[ -d libft ] && [ -f libft/Makefile ] && $(MAKE) -s --no-print-directory -C libft clean || true
	@echo $(RED)"Removing $(NAME) object files"$(DEFAULT);

# Remove all generated web artifacts (fixed name + any old versioned copies)
fclean: clean
# 	@rm -f $(NAME).html $(NAME).js $(NAME).wasm $(NAME).data $(NAME)-*.html
	@rm -rf MLX42
	@[ -d libft ] && [ -f libft/Makefile ] && $(MAKE) -s --no-print-directory -C libft fclean || true
	@rm -rf libft
	@echo $(RED)"Removing web files and MLX42"$(DEFAULT);

# Rebuild everything
re: fclean all
	@echo $(GREEN)"Rebuilding web version"$(DEFAULT);

.PHONY: all clean fclean re check-emscripten

# Colours
DEFAULT = "\033[39m"
GREEN   = "\033[32m"
RED     = "\033[31m"