TARGET:=build/rts
LDFLAGS:=$(shell pkg-config raylib -libs) -lm

.PHONY: all run

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): src/main.cpp | build/
	g++ -o $(TARGET) $(LDFLAGS) $^

build/:
	mkdir build

