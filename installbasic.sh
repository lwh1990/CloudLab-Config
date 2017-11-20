#!/bin/bash

sudo apt-get install gfortran vim unzip


# install mpich
scp /mnt/orangefs/app/mpich-3.2.tar.gz .

tar -zxvf mpich-3.2.tar.gz

cd mpich-3.2/

./configure --enable-romio --with-file-system=ufs+pvfs2 CPPFLAGS="-I/opt/orangefs/include"  LDFLAGS="-L/opt/orangefs/lib" LIBS="-lpvfs2"

make -j

sudo make install
