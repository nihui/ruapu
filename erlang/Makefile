ifndef MIX_APP_PATH
	MIX_APP_PATH=$(shell pwd)
endif

PRIV_DIR = $(MIX_APP_PATH)/priv
RUAPU_SO = $(PRIV_DIR)/ruapu.so
C_SRC = $(shell pwd)/c_src

ERTS_INCLUDE_DIR = $(shell erl -noshell -eval "io:format('~ts/erts-~ts/include/', [code:root_dir(), erlang:system_info(version)]), halt().")
CFLAGS += -shared -O3 -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -fPIC -I$(ERTS_INCLUDE_DIR)

UNAME_S := $(shell uname -s)
ifndef TARGET_ABI
ifeq ($(UNAME_S),Darwin)
	TARGET_ABI = darwin
endif
endif

ifeq ($(TARGET_ABI),darwin)
	CFLAGS += -undefined dynamic_lookup -flat_namespace
endif

.DEFAULT_GLOBAL := build

build: $(RUAPU_SO)
	@echo > /dev/null

$(RUAPU_SO): $(C_SRC)/ruapu.c
	@ mkdir -p $(PRIV_DIR)
	$(CC) $(CFLAGS) $(C_SRC)/ruapu.c -o $(RUAPU_SO)
