CXX=g++
CFLAGS=-Wall -g -I../../include -std=c++11
LDFLAGS=

OBJDIR = obj/
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

all: 1dv434.s2.l1

1dv434.s2.l1: ${OBJS}
	${CXX} ${CFLAGS} ${OBJS} ../../lib/zlib.a ${LDFLAGS} -o 1dv434.s2.l1

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	${CXX} ${CFLAGS} ${LDFLAGS} -c $< -o $@

clean:
	rm -f ${OBJS} 1dv434.s2.l1
