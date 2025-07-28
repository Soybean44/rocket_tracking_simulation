TARGET:=build/rts
LDFLAGS:=$(shell pkg-config raylib -libs) -lm
CFLAGS:=$(shell pkg-config raylib -cflags) -Wall

.PHONY: all run

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): build/main.o build/track.o
	g++ -o $@ $(LDFLAGS)  $?

build/%.o : src/%.cpp | build/
	g++ -o $@ $(CFLAGS) -c $^


build/:
	mkdir build

