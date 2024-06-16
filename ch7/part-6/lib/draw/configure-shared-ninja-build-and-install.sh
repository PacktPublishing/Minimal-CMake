#!/bin/bash

./configure-shared-ninja.sh
cmake --build build/shared-ninja --config Release --target install
