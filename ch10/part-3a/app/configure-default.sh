#!/bin/bash

cmake -B build -G "Ninja Multi-Config" -DSUPERBUILD=ON -DMC_GOL_SHARED=ON -DMC_DRAW_SHARED=ON \
  -DCMAKE_PREFIX_PATH=third-party/install \
  -DCMAKE_INSTALL_PREFIX=install
