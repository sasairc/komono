#!/bin/sh

ARCH="x86"
VER=$(grep Linux/${ARCH} .config | cut -d ' ' -f 3)

cp arch/${ARCH}/boot/bzImage /boot/vmlinuz-${VER}	&& \
cp System.map /boot/System.map-${VER}				&& \
cp .config /boot/config-${VER}						&& \
mkinitramfs -o /boot/initrd.img-${VER} ${VER}
