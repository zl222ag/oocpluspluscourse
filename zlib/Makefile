CXX=g++
CFLAGS=-Wall -g -fPIC -I../include -std=c++11
LDFLAGS=

OUTDIR = bin/

OBJDIR = obj/
SRCS = $(wildcard ../source/*.cpp)
OBJS = $(patsubst ../source/%.cpp,$(OBJDIR)/%.o,$(SRCS))

all: zlib.a

zlib.a: ${OBJS}
	mkdir -p ${OUTDIR}
	ar -cvq ${OUTDIR}/$@ ${OBJS}

$(OBJDIR)/%.o: ../source/%.cpp
	mkdir -p $(dir $@)
	${CXX} ${CFLAGS} ${LDFLAGS} -c $< -o $@

clean:
	rm -rfv obj/ bin/
