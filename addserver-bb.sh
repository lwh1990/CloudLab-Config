#!/bin/bash

scp -rp node4:/ssd/orangefs /ssd

rm -rf /ssd/orangefs/storage

sudo /ssd/orangefs/sbin/pvfs2-server -f /ssd/orangefs/etc/orangefs-server.conf -a node$1

sudo /ssd/orangefs/sbin/pvfs2-server  /ssd/orangefs/etc/orangefs-server.conf -a node$1


