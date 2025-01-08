
all:
	@g++ -std=c++11 -o cctest -g -O0 testccout.cpp ./src/ccout.cpp -I ./include

.PHONY:
clean:
	@rm -f cctest
	@rm -rf cctest*
