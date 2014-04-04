LDFLAGS=-framework ParallelsVirtualizationSDK
PREFIX=.

all:
	mkdir -p $(PREFIX)/bin
	gcc -o $(PREFIX)/bin/prltype $(LDFLAGS) src/prltype.cpp

clean:
	rm -rf $(PREFIX)/bin/

