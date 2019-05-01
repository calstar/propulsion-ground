build_target = NUCLEO_F401RE
build_toolchain = GCC_ARM
build_dir = BUILD
project_name = prop_remote

outdir = out/
outname = prop_remote.bin
outpath = $(outdir)$(outname)

FLATC = ../general/flatc

OS := $(shell uname)
ifeq ($(OS), Darwin)
FLATC = ../general/flatc_mac
endif

build: prop_downlink_generated.h prop_uplink_generated.h
	time mbed compile --target $(build_target) --toolchain $(build_toolchain) \
	&& mkdir -p $(outdir) && cp $(build_dir)/$(build_target)/$(build_toolchain)/$(project_name).bin $(outpath) \
	&& echo "Copied output to $(outpath)"

flash: validate
	st-flash write $(outpath) 0x8000000

%_generated.h: ../general/%.fbs
	$(FLATC) --cpp $<
