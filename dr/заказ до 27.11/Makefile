.PHONY: all clean

all:
	g++ -o studetns students.cpp
	g++ -o stack stack.cpp
	g++ -o queue queue.cpp
	g++ -o circlelist circlelist.cpp
	g++ -o arrlist arrlist.cpp
	g++ -o avl avl_templ.cpp
	g++ -o coder ./eben/functions.h ./eben/functions.cpp ./eben/coder.cpp
	g++ -o decoder ./eben/functions.h ./eben/functions.cpp ./eben/decoder.cpp

play:
	echo "_______STUDETNS_______"
	./studetns
	echo "_______STACK_______"
	./stack
	echo "_______QUEUE_______"
	./queue
	echo "_______CIRCLELIST_______"
	./circlelist
	echo "_______ARRLIST_______"
	./arrlist
	echo "_______AVL_______"
	./avl
	echo "_______CODER_______"	
	./coder	
	cat ./input
	cat ./output
	echo "_______DECODER_______"
	./decoder	
	cat ./result

clean:
	rm -rf studetns
	rm -rf stack
	rm -rf queue
	rm -rf circlelist
	rm -rf arrlist
	rm -rf avl
	rm -rf coder
	rm -rf decoder
	rm -rf coded
	rm -rf result

