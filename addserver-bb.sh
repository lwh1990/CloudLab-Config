#!/bin/bash

./ssd.sh

scp -rp server4:/ssd/orangefsbb /ssd

rm -rf /ssd/orangefsbb/storage

sudo /ssd/orangefsbb/sbin/pvfs2-server -f /ssd/orangefsbb/etc/orangefs-server.conf -a server$1

sudo /ssd/orangefsbb/sbin/pvfs2-server  /ssd/orangefsbb/etc/orangefs-server.conf -a server$1


