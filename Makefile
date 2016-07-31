SOURCES=main.c postdrop.c
FLAGS=lib/libcrypto.a lib/liboath.a lib/libcurl.a lib/libjansson.a -lssl -lcrypto -lssl -lcrypto -lz -DCURL_STATICLIB -Iinclude
TARGET=postdrop

all:
	cc $(SOURCES) $(FLAGS) -o $(TARGET)
debug:
	cc $(SOURCES) $(FLAGS) -ggdb -o $(TARGET)
clean:
	rm $(TARGET)
