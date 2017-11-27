#!/bin/basg
sudo apt install automake build-essential bison flex libattr1 libattr1-dev

tar -xzvf orangefs-2.9.6.tar.gz

cd orangefs-2.9.6

./configure --prefix=/ssd/orangefs --with-kernel=/lib/modules/3.13.0-117-generic/build --with-db-backend=lmdb --enable-shared

make 

sudo make install

make kmod

sudo make kmod_prefix=/ssd/orangefs kmod_install

sudo /ssd/orangefs/bin/pvfs2-genconfig /ssd/orangefs/etc/orangefs-server.conf 

sudo /ssd/orangefs/sbin/pvfs2-server -f /ssd/orangefs/etc/orangefs-server.conf -a node4

sudo /ssd/orangefs/sbin/pvfs2-server  /ssd/orangefs/etc/orangefs-server.conf -a node4


