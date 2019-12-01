include variables.mk

GST_PREFIX := gst-build

GST_LIB_BC := \
	build/subprojects/gstreamer/libs/gst/net/libgstnet-1.0.so.0.1700.0.bc \
	build/subprojects/gstreamer/libs/gst/base/libgstbase-1.0.so.0.1700.0.bc \
	build/subprojects/gstreamer/libs/gst/controller/libgstcontroller-1.0.so.0.1700.0.bc \
	build/subprojects/gstreamer/gst/libgstreamer-1.0.so.0.1700.0.bc \
	build/subprojects/gstreamer/libs/gst/check/libgstcheck-1.0.so.0.1700.0.bc \

GST_LIB_BC := $(addprefix $(GST_PREFIX)/,$(GST_LIB_BC))

GST_LIB_IR=$(patsubst %.bc,%.ll,$(GST_LIB_BC))

# Helper target build gstreamer
gstreamer :
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(LLVM_INSTALL_PREFIX)/lib PATH=$(LLVM_INSTALL_PREFIX)/bin:$(PATH) ./build-gstreamer.sh

all : all-reports

%.ll : %.bc
	PATH=$(LLVM_INSTALL_PREFIX)/bin:$(PATH) llvm-dis $^

# Build all library .ll files
libs-ll : $(GST_LIB_IR)

TEST_PREFIX := $(GST_PREFIX)/build/subprojects/gst-plugins-bad/tests/check

TEST_BC := $(wildcard $(TEST_PREFIX)/*.bc)
TEST_LL := $(patsubst %.bc,%.ll,$(TEST_BC))

CG_ANALYSIS ?= OTF # CHA, RTA, etc.

# Build all test .ll files
tests-ll : $(TEST_LL)

empty=
blank := $(empty) $(empty)

%.linked.bc : %.bc $(GST_LIB_BC)
	PATH=$(LLVM_INSTALL_PREFIX)/bin:$(PATH) llvm-link $(GST_LIB_BC) $< -o $@

# Generate analysis reports for all tests
%.linked.report : %.linked.ll
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(PHASAR_INSTALL_PREFIX)/lib:$(LLVM_INSTALL_PREFIX)/lib $(PHASAR_BINARY_PATH)/phasar --data-flow-analysis=IDE_GObjAnalysis --pointer-analysis=CFLAnders --callgraph-analysis=$(CG_ANALYSIS) --module=$< --output=$@


# Generate analysis reports for all tests
%.report : %.ll $(GST_LIB_IR)
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(PHASAR_INSTALL_PREFIX)/lib:$(LLVM_INSTALL_PREFIX)/lib $(PHASAR_BINARY_PATH)/phasar --data-flow-analysis=IDE_GObjAnalysis --pointer-analysis=CFLAnders --callgraph-analysis=$(CG_ANALYSIS) $(addprefix "--module=", $^) --output=$@

ALL_REPORTS := $(patsubst %.ll,%.linked.report,$(TEST_LL))

all-reports : $(ALL_REPORTS)
