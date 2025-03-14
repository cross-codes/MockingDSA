COMPILER = icpx
FLAGS = -xc++ -std=c++23 -O2 -I/home/cross/MockingDSA/lib \
				-funroll-loops -fsanitize=undefined,address -fno-sanitize-recover \
				-Wall -Wextra -Wshadow -Wconversion -Wfloat-equal -Wno-unused-const-variable \
				-Wno-sign-conversion -Wshift-overflow -Wcast-qual -Wcast-align \
				-DCROSS -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_GLIBCXX_SANITIZE_VECTOR \
				-D_FORTIFY_SOURCE=2 -g -Wl,-z,stack-size=268435456
all:
	$(COMPILER) $(FLAGS) $(FILE) -o sol.x86_64
