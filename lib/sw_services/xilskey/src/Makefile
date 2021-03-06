###############################################################################
#
# Copyright (C) 2013 - 2015 Xilinx, Inc.  All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# Use of the Software is limited solely to applications:
# (a) running on a Xilinx device, or
# (b) that interact with a Xilinx device through a bus or interconnect.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
# OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# Except as contained in this notice, the name of the Xilinx shall not be used
# in advertising or otherwise to promote the sale, use or other dealings in
# this Software without prior written authorization from Xilinx.
#
###############################################################################

COMPILER=
ARCHIVER=
CP=cp
COMPILER_FLAGS=
EXTRA_COMPILER_FLAGS=
LIB= libxilskey.a

EXTRA_ARCHIVE_FLAGS=rc
RELEASEDIR=../../../lib
INCLUDEDIR=../../../include
INCLUDES=-I./. -I${INCLUDEDIR}

SKEY_DIR = .
OUTS = *.o

SKEY_SRCS := $(wildcard *.c)
SKEY_OBJS = $(addprefix $(SKEY_DIR)/, $(SKEY_SRCS:%.c=%.o))

INCLUDEFILES=$(SKEY_DIR)/include/xilskey_eps.h \
			$(SKEY_DIR)/include/xilskey_epl.h \
			$(SKEY_DIR)/include/xilskey_utils.h \
			$(SKEY_DIR)/include/xilskey_bbram.h \
			$(SKEY_DIR)/include/xilskey_eps_zynqmp.h \
			$(SKEY_DIR)/include/xilskey_eps_zynqmp_puf.h

libs: libxilskey.a

libxilskey.a: print_msg_xilskey $(SKEY_OBJS)
	$(ARCHIVER) $(EXTRA_ARCHIVE_FLAGS) ${RELEASEDIR}/${LIB} ${SKEY_OBJS}

print_msg_xilskey:
	@echo "Compiling Xilskey Library"

.PHONY: include
include: libxilskey_includes

libxilskey_includes:
	${CP} ${INCLUDEFILES} ${INCLUDEDIR}

clean:
	rm -rf $(SKEY_DIR)/${OUTS}
	rm -rf ${RELEASEDIR}/${LIB}

$(SKEY_DIR)/%.o: $(SKEY_DIR)/%.c $(INCLUDEFILES)
	$(COMPILER) $(COMPILER_FLAGS) $(EXTRA_COMPILER_FLAGS) $(INCLUDES) -c $< -o $@
