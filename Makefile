SOURCES=src/main.c src/postdrop.c src/trim.c
FLAGS=lib/liboath.a lib/libjansson.a  -lcurl -lssl -lcrypto -lz -Iinclude
TARGET=postdrop

all:
	cc $(SOURCES) $(FLAGS) -o $(TARGET)
debug:
	cc $(SOURCES) $(FLAGS) -ggdb -o $(TARGET)
clean:
	rm $(TARGET)
