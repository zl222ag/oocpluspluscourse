CXX=g++
CFLAGS=-Wall -Wno-unknown-pragmas -g -I../../include -std=c++11
LDFLAGS=

OBJDIR = obj/
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

all: 1dv434.s2.l3

1dv434.s2.l3: ${OBJS}
	${CXX} ${CFLAGS} ${OBJS} ../../lib/zlib.a ${LDFLAGS} -o $@

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	${CXX} ${CFLAGS} ${LDFLAGS} -c $< -o $@

clean:
	rm -f ${OBJS} 1dv434.s2.l3
