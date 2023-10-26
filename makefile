SOURCE_main := $(shell find ./ -name '*.cpp')

output: $(SOURCE_main)
		g++ -o compilado $(SOURCE_main)

