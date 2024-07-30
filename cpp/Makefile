#!/bin/make
OUTDIR	= ./build
TARGET	= $(OUTDIR)/raw_socket_sample
SOURCES	= $(wildcard *.cpp)
OBJECTS	= $(addprefix $(OUTDIR)/, $(SOURCES:.cpp=.o))

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(TARGET)

.PHONY: run
run: $(TARGET)
	$(TARGET)

$(TARGET): $(OBJECTS) Makefile
	$(CXX) -O0 -g -pthread -o $(TARGET) $(OBJECTS)

$(OUTDIR)/%.o: %.cpp Makefile
	mkdir -p build
	$(CXX) -O0 -g -o $@ -c $<
