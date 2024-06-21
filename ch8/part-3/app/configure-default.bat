@echo off

cmake -B build -G "Ninja Multi-Config" -DSUPERBUILD=ON -DCMAKE_PREFIX_PATH=third-party/install
