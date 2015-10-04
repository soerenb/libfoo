CC ?= gcc
AR = gcc-ar
CFLAGS = -Wall -O3 -march=native -D_FORTIFY_SOURCE=2 -fstack-protector-strong \
	 -Iinclude -flto -ffat-lto-objects -fdiagnostics-color=auto -fpic
LDFLAGS = -shared

LIBNAME = foo
LIBDIR = lib
TARGET_LIB = ${LIBDIR}/lib${LIBNAME}.a
TARGET_SLIB = ${LIBDIR}/lib${LIBNAME}.so.1
SOURCES = src/gets.c src/chkuadd.c src/chkadd.c src/filesize.c src/gopt.c
OBJECTS = $(addsuffix .o, $(basename ${SOURCES}))

all: ${TARGET_LIB} ${TARGET_SLIB}

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
cc_o_so = ${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^
quiet_cc_o_so = LD $@

%.o: %.c
	@echo "$(${quiet}cc_c_o)"
	@${call cc_c_o}

${TARGET_LIB}: ${OBJECTS} | ${LIBDIR}
	@echo "$(${quiet}ar_o_a)"
	@${call ar_o_a}

${TARGET_SLIB}: ${OBJECTS} | ${LIBDIR}
	@echo "$(${quiet}cc_o_so)"
	@${call cc_o_so}

${LIBDIR}:
	${Q}mkdir -p ${LIBDIR}

.PHONY: clean
clean:
	rm -rf ${TARGET_LIB} ${TARGET_SLIB} ${OBJECTS} $(OBJECTS:.o=.d)

.PHONY: distclean
distclean: clean
	rm -rf ${LIBDIR}
