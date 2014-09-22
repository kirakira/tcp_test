.PHONY:
	all

all: client.cc server_slow.cc server_fast.cc
	c++ -O2 -o server_slow server_slow.cc
	c++ -O2 -o server_fast server_fast.cc
	c++ -O2 -o client client.cc
