#!/bin/bash

sudo apt-get update
sudo apt-get install mpich cmake

# install ROSS
git clone http://github.com/carothersc/ROSS.git
cd ROSS
mkdir build
cd build
ARCH=x86_64 CC=mpicc CXX=mpicxx cmake -DCMAKE_INSTALL_PREFIX=../install ../
make -j
make install
cd ~

# install codes
tar -zxvf codes-0.6.0.tar.gz
cd codes-0.6.0
./prepare.sh
mkdir install
./configure --prefix=/users/lwh1990/codes-0.6.0/install CC=mpicc CXX=mpicxx PKG_CONFIG_PATH=/users/lwh1990/ROSS/install/lib/pkgconfig
make -j
make install

