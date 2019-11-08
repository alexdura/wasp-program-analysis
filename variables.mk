# This is a file where you should define some paths to that makefiles can use them
# GLIB
# GLib installation path
GLIB_INSTALL_PREFIX ?= /usr

# We set the include and lib path automatically (for use in -I and -L options given to clang)
GLIB_INCLUDE_PATH = $(GLIB_INSTALL_PREFIX)/include/glib-2.0
GLIB_LIB_PATH = $(GLIB_INSTALL_PREFIX)/lib/x86_64-linux-gnu

# Glib_config
GLIB_CONFIG_INCLUDE_PATH = $(GLIB_LIB_PATH)/glib-2.0/include/

# PHASAR
# Phasar installation path
PHASAR_INSTALL_PREFIX ?= /home/noric/Dev/wasp-project-course/wasp-program-analysis/phasar

# We derive the include path automatically
PHASAR_INCLUDE_PATH ?= $(PHASAR_INSTALL_PREFIX)/include

# The path for the Phasar binary
PHASAR_BINARY_PATH ?= $(PHASAR_INSTALL_PREFIX)/build

# LLVM
LLVM_INSTALL_PREFIX ?= /home/noric/Dev/wasp-project-course/wasp-program-analysis/llvm/llvm_install

LLVM_INCLUDE_PATH ?= $(LLVM_INSTALL_PREFIX)/include

# wise_enum
WISE_ENUM_INCLUDE_PATH ?= $(PHASAR_INSTALL_PREFIX)/external/wise_enum
