LDFLAGS=-framework ParallelsVirtualizationSDK
PREFIX=.

CPPFLAGS=-g -D_REENTRANT -I./src

prltype: prltype.o common.o
	gcc $(LDFLAGS) -o $(PREFIX)/bin/prltype out/prltype.o out/common.o
	chmod 555 $(PREFIX)/bin/prltype

prltype.o: setup
	gcc $(CPPFLAGS) -c src/prltype.cpp -o out/prltype.o

common.o: setup
	gcc $(CPPFLAGS) -c src/common.cpp -o out/common.o

setup:
	mkdir -p $(PREFIX)/bin
	mkdir -p out

clean:
	rm -rf $(PREFIX)/bin
	rm -rf out
