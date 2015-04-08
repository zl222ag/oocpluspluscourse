CXX=g++
CFLAGS=-Wall -I../../include -std=c++11
LDFLAGS=../../lib/zlib.a TakeFive.o

OBJDIR = obj/
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

all: takefive

takefive: ${OBJS}
	${CXX} -g ${CFLAGS} ${OBJS} ${LDFLAGS} -o takefive

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	${CXX} ${CFLAGS} ${LDFLAGS} -c $< -o $@

clean:
	rm -f ${OBJS} takefive
