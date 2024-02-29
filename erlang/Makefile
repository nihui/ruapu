ifndef MIX_APP_PATH
	MIX_APP_PATH=$(shell pwd)
endif

PRIV_DIR = $(MIX_APP_PATH)/priv
RUAPU_SO = $(PRIV_DIR)/ruapu_nif.so
C_SRC = $(shell pwd)/c_src

.DEFAULT_GLOBAL := build

build: $(RUAPU_SO)
	@echo > /dev/null

$(RUAPU_SO): $(C_SRC)/ruapu.c
	@ cmake -S . -B "$(PRIV_DIR)/cmake_ruapu" \
		-DCMAKE_BUILD_TYPE=Release \
		-DC_SRC=$(C_SRC) \
		-DMIX_APP_PATH=$(MIX_APP_PATH) \
		-DCMAKE_INSTALL_PREFIX=$(PRIV_DIR)
	@ cmake --build "$(PRIV_DIR)/cmake_ruapu" --config Release
	@ cp "$(PRIV_DIR)/cmake_ruapu/ruapu_nif.so" $(RUAPU_SO)
