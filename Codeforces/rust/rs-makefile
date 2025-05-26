FILE ?= my_program

all: build move

build:
		cargo build --bin $(FILE)

move:
		cp target/debug/$(FILE) ./sol.x86_64
