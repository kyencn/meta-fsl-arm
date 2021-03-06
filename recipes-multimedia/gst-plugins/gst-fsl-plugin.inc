# Copyright (C) 2011-2013 Freescale Semiconductor
# Released under the MIT license (see COPYING.MIT for the terms)

DESCRIPTION = "Gstreamer freescale plugins"
LICENSE = "GPLv2 & LGPLv2 & LGPLv2.1"
SECTION = "multimedia"

DEPENDS = "gstreamer gst-plugins-base libfslcodec libfslparser virtual/kernel"
DEPENDS_append_mx5 = " imx-lib"
DEPENDS_append_mx6 = " imx-lib libfslvpuwrap"

LIC_FILES_CHKSUM = "file://COPYING;md5=59530bdf33659b29e73d4adb9f9f6552 \
                    file://COPYING-LGPL-2;md5=5f30f0716dfdd0d91eb439ebec522ec2 \
                    file://COPYING-LGPL-2.1;md5=fbc093901857fcd118f065f900982c24"

S = "${WORKDIR}/gst-fsl-plugins-${PV}"

SRC_URI = "${FSL_MIRROR}/gst-fsl-plugins-${PV}.tar.gz"

inherit autotools pkgconfig

PLATFORM_mx5 = "MX51"
PLATFORM_mx6 = "MX6"
PLATFORM_mx28 = "MX28"

# Todo add a mechanism to map posible build targets
INCLUDE_DIR = "-I${STAGING_KERNEL_DIR}/include"
EXTRA_OEMAKE = "INCLUDES=${INCLUDE_DIR}"
EXTRA_OECONF = "PLATFORM=${PLATFORM} --disable-valgrind --disable-examples --disable-debug"
CACHED_CONFIGUREVARS += "CROSS_ROOT=${STAGING_DIR_TARGET}"

PACKAGES += "${PN}-libmfwsconf ${PN}-libgplaycore ${PN}-libgstfsl \
             ${PN}-libme ${PN}-libgstbufmeta ${PN}-libmfwba \
             ${PN}-libfwvss ${PN}-gplay"

# FIXME: Add all features
# feature from excluded mm packages
PACKAGECONFIG[ac3] += "--enable-ac3dec,--disable-ac3dec,libfslac3codec"
# feature from special mm packages
PACKAGECONFIG[aacp] += "--enable-aacpdec,--disable-aacpdec,libfslaacpcodec"
MSDEPENDS = "libfslmsparser libfslmscodec"
PACKAGECONFIG[wma10dec] +="--enable-wma10dec,--disable-wma10dec,${MSDEPENDS}"
PACKAGECONFIG[wma8enc] +="--enable-wma8enc,--disable-wma8enc,${MSDEPENDS}"
PACKAGECONFIG[wmv9mpdec] +="--enable-wmv9mpdec,--disable-wmv9mpdec,${MSDEPENDS}"
PACKAGECONFIG[wmv78dec] +="--enable-wmv78dec,--disable-wmv78dec,${MSDEPENDS}"

FILES_${PN} = "${libdir}/gstreamer-0.10/*.so ${datadir}"
RDEPENDS_${PN} += "gst-plugins-good-id3demux libfslparser"

FILES_${PN}-dbg += "${libdir}/gstreamer-0.10/.debug"
FILES_${PN}-dev += "${libdir}/gstreamer-0.10/*.la ${libdir}/pkgconfig/*.pc"
FILES_${PN}-staticdev += "${libdir}/gstreamer-0.10/*.a"

FILES_${PN}-gplay = "${bindir}/gplay"
FILES_${PN}-libmfwsconf = "${libdir}/libmfwsconf${SOLIBS}"
FILES_${PN}-libgplaycore = "${libdir}/libgplaycore${SOLIBS}"
FILES_${PN}-libgstfsl = "${libdir}/libgstfsl-0.10${SOLIBS}"
FILES_${PN}-libme = "${libdir}/libme${SOLIBS}"
FILES_${PN}-libgstbufmeta = "${libdir}/libgstbufmeta${SOLIBS}"
FILES_${PN}-libmfwba =  "${libdir}/libmfwba${SOLIBS}"
FILES_${PN}-libfwvss = "${libdir}/libmfwvss${SOLIBS}"

PACKAGE_ARCH = "${MACHINE_ARCH}"
