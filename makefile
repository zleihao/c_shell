# 纯属懒
#strat
TARGET = shell.out
SRCS = $(shell find ./ -name "*.c")
DIR = -I "./cmd" -I "./shell"

$(TARGET): $(SRCS:.c = .o)
	gcc $^ -o $@ $(DIR)

#end
