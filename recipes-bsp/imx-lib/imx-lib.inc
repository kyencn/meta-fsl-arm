# Copyright (C) 2012-2013 Freescale Semiconductor

DESCRIPTION = "Platform specific libraries for imx platform"
LICENSE = "LGPLv2.1"
SECTION = "multimedia"
DEPENDS = "virtual/kernel"

LIC_FILES_CHKSUM = "file://ipu/mxc_ipu_hl_lib.h;endline=13;md5=6c7486b21a8524b1879fa159578da31e"

inherit fsl-eula-unpack

PLATFORM_mx6 = "IMX6Q"
PLATFORM_mx5 = "IMX51"

PARALLEL_MAKE="-j 1"
EXTRA_OEMAKE = ""

do_configure_append () {
    # FIXME: The build system does not allow CC and AR to be overriden
    find ${S} -name Makefile | xargs sed -i 's,^\(CC\|AR\)=,\1 ?=,g'
}

do_compile () {
    INCLUDE_DIR="-I${STAGING_INCDIR} -I${STAGING_KERNEL_DIR}/drivers/mxc/security/rng/include \
                 -I${STAGING_KERNEL_DIR}/drivers/mxc/security/sahara2/include \
                 -I${STAGING_KERNEL_DIR}/include"
    oe_runmake CROSS_COMPILE="${HOST_PREFIX}" PLATFORM="${PLATFORM}" INCLUDE="${INCLUDE_DIR}" all
}

do_install () {
    oe_runmake PLATFORM="${PLATFORM}" DEST_DIR="${D}" install
}
