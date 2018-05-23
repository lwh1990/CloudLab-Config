#!/bin/bash

sudo scp -rp server0:/hdd/orangefs /opt

sudo insmod /opt/orangefs/lib/modules/3.13.0-143-generic/kernel/fs/pvfs2/pvfs2.ko

sudo cp /opt/orangefs/lib/* /usr/lib/

sudo /opt/orangefs/sbin/pvfs2-client

sudo mkdir /mnt/orangefs

sudo sh -c "echo 'tcp://server0:3334/orangefs /mnt/orangefs pvfs2' >> /etc/pvfs2tab"

sudo mount -t pvfs2 tcp://server0:3334/orangefs /mnt/orangefs
