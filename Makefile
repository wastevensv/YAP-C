SOURCES=main.c postdrop.c trim.c
FLAGS=lib/liboath.a lib/libcurl.a lib/libjansson.a  -lssl -lcrypto -lz -DCURL_STATICLIB -Iinclude
TARGET=postdrop

all:
	cc $(SOURCES) $(FLAGS) -o $(TARGET)
debug:
	cc $(SOURCES) $(FLAGS) -ggdb -o $(TARGET)
clean:
	rm $(TARGET)
