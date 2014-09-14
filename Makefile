CC ?= gcc
AR = gcc-ar
CFLAGS = -Wall -O3 -march=native -D_FORTIFY_SOURCE=2 -fstack-protector-strong \
	 -Iinclude -flto -ffat-lto-objects -fdiagnostics-color=auto

LIBNAME = foo
LIBDIR = lib
TARGET_LIB = ${LIBDIR}/lib${LIBNAME}.a
SOURCES = src/gets.c src/chkuadd.c src/chkadd.c src/filesize.c src/gopt.c
OBJECTS = $(addsuffix .o, $(basename ${SOURCES}))

.PHONY: clean distclean

all: ${TARGET_LIB}

-include $(OBJECTS:.o=.d)

debug: CXXFLAGS+=-O0 -g -p -U_FORTIFY_SOURCE
debug: CFLAGS+=-O0 -g -p -U_FORTIFY_SOURCE
debug: all

ifdef V
quiet =
Q =
else
quiet = quiet_
Q = @
endif

cc_c_o = ${CC} -c ${CFLAGS} ${SYMBOLS} -MMD -MP -o $@ $<
quiet_cc_c_o = CC $@
ar_o_a = ${AR} rcs $@ $^
quiet_ar_o_a = AR $@

%.o: %.c
	@echo "$(${quiet}cc_c_o)"
	@${call cc_c_o}

${TARGET_LIB}: ${OBJECTS} | ${LIBDIR}
	@echo "$(${quiet}ar_o_a)"
	@${call ar_o_a}

${LIBDIR}:
	${Q}mkdir -p ${LIBDIR}

clean:
	rm -rf ${TARGET_LIB} ${OBJECTS} $(OBJECTS:.o=.d)

distclean: clean
	rm -rf ${LIBDIR}
