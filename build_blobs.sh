#!/bin/sh
if [ -z "$NDK" ]  ; then
  if [ ~/"android-ndk-*" = ~/'android-ndk-*' ] ; then
    echo "Please set NDK to your Android NDK directory"
    exit 1
  else
     NDK=~/"android-ndk-*"
  fi
fi

export NDK
export SYSROOT=$NDK/platforms/android-15/arch-x86
export CC="$NDK/toolchains/x86-4.6/prebuilt/linux-x86_64/bin/i686-linux-android-gcc --sysroot=$SYSROOT"

make clean all gxi_dump_images
mkdir medfield_bin 2> /dev/null
mv gxi_pack medfield_bin/pack
mv gxi_unpack medfield_bin/unpack
mv gxi_dump_images medfield_bin/dump_images
make clean
