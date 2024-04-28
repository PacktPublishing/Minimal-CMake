#!/bin/bash

# compile shaders

mkdir -p shader/build

# simple shader
../third-party/install/bin/shaderc \
-f shader/vs_vertcol.sc -o shader/build/vs_vertcol.bin \
--platform osx --type vertex --verbose -i ./ -p metal

../third-party/install//bin/shaderc \
-f shader/fs_vertcol.sc -o shader/build/fs_vertcol.bin \
--platform osx --type fragment --verbose -i ./ -p metal
