#!/bin/bash

cd /mnt/orangefs/
mkdir ior
cd ior

cp /local/repository/parallel-netcdf-1.8.1.tar.gz .
cp /local/repository/ior-master.zip .

#install pnetcdf
tar -zxvf parallel-netcdf-1.8.1.tar.gz
cd parallel-netcdf-1.8.1/
./configure
make -j
sudo make install

cd ..

#install ior
unzip ior-master.zip
cd ior-master/
mkdir build
./bootstrap
./configure --prefix=/mnt/orangefs/ior/ior-master/build --with-ncmpi
make
make install
