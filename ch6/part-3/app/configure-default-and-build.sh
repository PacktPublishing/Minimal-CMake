#!/bin/bash

./configure-default.sh
cmake --build build --config Debug 
cmake --build build --config RelWithDebInfo
