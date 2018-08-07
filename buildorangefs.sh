#!/bin/bash
sudo apt install automake build-essential bison flex libattr1 libattr1-dev vim

./hdd.sh

tar -xzvf orangefs-2.9.6.tar.gz

cd orangefs-2.9.6

./configure --prefix=/hdd/orangefs --with-kernel=/lib/modules/3.13.0-143-generic/build --with-db-backend=lmdb --enable-shared

make 

sudo make install

make kmod

sudo make kmod_prefix=/hdd/orangefs kmod_install

sudo /hdd/orangefs/bin/pvfs2-genconfig /hdd/orangefs/etc/orangefs-server.conf 

sudo /hdd/orangefs/sbin/pvfs2-server -f /hdd/orangefs/etc/orangefs-server.conf -a server0

sudo /hdd/orangefs/sbin/pvfs2-server  /hdd/orangefs/etc/orangefs-server.conf -a server0


