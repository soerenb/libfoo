CC ?= gcc
AR ?= ar
CFLAGS = -Wall -O3 -march=native -D_FORTIFY_SOURCE=2

LIBNAME = foo
LIBDIR = lib
TARGET_LIB = ${LIBDIR}/lib${LIBNAME}.a
SOURCES = src/gets.c src/chkuadd.c src/chkadd.c src/filesize.c
OBJECTS = $(addsuffix .o, $(basename ${SOURCES}))

.PHONY: clean distclean

all: ${TARGET_LIB}

debug: CXXFLAGS+=-O0 -g -p
debug: CFLAGS+=-O0 -g -p
debug: all

ifdef MAKEVERBOSE
quiet =
Q =
else
quiet = quiet_
Q = @
endif

cc_c_o = "${CC} -c ${CFLAGS} ${SYMBOLS} -o $@ $<"
quiet_cc_c_o = "CC $@"
cc_o_a = "${AR} rcs $@ ${OBJECTS}"
quiet_cc_o_a = "AR $@"

%.o: %.c
	@echo "$(${quiet}cc_c_o)"
	@${CC} -c ${CFLAGS} ${SYMBOLS} -o $@ $<

${TARGET_LIB}: ${OBJECTS} | ${LIBDIR}
	@echo "$(${quiet}cc_o_a)"
	@${AR} rcs $@ ${OBJECTS}

${LIBDIR}:
	${Q}mkdir -p ${LIBDIR}

clean:
	rm -rf ${TARGET_LIB} ${OBJECTS}

distclean: clean
	rm -rf ${LIBDIR}