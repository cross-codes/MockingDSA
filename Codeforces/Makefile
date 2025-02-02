COMPILER = icpx
FLAGS = -xc++ -std=c++23 -O2 -I/home/cross/MockingDSA/lib -funroll-loops \
				-fsanitize=undefined,address -fno-sanitize-recover -fstack-protector \
				-Wall -Wextra -Wshadow -Wconversion -Wfloat-equal \
				-Wno-unused-const-variable -Wno-sign-conversion -Wshift-overflow \
				-Wcast-qual -Wcast-align -Wno-unused-result -DCROSS -D_GLIBCXX_DEBUG \
				-D_GLIBCXX_DEBUG_PEDANTIC -D_GLIBCXX_SANITIZE_VECTOR \
				-D_FORTIFY_SOURCE=2 -g
all:
	$(COMPILER) $(FLAGS) $(FILE) -o sol.x86_64
