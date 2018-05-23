#!/bin/bash
sudo apt install automake build-essential bison flex libattr1 libattr1-dev

./ssd.sh

tar -xzvf orangefs-2.9.6.tar.gz

cd orangefs-2.9.6

./configure --prefix=/ssd/orangefsbb --with-kernel=/lib/modules/3.13.0-143-generic/build --with-db-backend=lmdb --enable-shared

make 

sudo make install

make kmod

sudo make kmod_prefix=/ssd/orangefsbb kmod_install

sudo /ssd/orangefsbb/bin/pvfs2-genconfig /ssd/orangefsbb/etc/orangefs-server.conf 

sudo /ssd/orangefsbb/sbin/pvfs2-server -f /ssd/orangefsbb/etc/orangefs-server.conf -a server4

sudo /ssd/orangefsbb/sbin/pvfs2-server  /ssd/orangefsbb/etc/orangefs-server.conf -a server4


