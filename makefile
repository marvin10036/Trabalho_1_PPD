SOURCE_main := $(shell find ./ -name '*.c')

output: $(SOURCE_main)
		gcc -o compilado $(SOURCE_main)

