#!/bin/bash

cmake -B build -G "Ninja Multi-Config" -DCMAKE_PREFIX_PATH="../third-party/install;../lib/array/install;../lib/gol/install;../lib/draw/install" -DCMAKE_MODULE_PATH=../cmake -Dmc-gol_PATH=../lib/gol/install
