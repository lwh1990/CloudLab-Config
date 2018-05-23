#!/bin/bash

./hdd.sh

scp -rp server0:/hdd/orangefs /hdd

rm -rf /hdd/orangefs/storage

sudo /hdd/orangefs/sbin/pvfs2-server -f /hdd/orangefs/etc/orangefs-server.conf -a server$1

sudo /hdd/orangefs/sbin/pvfs2-server  /hdd/orangefs/etc/orangefs-server.conf -a server$1


