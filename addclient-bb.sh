#!/bin/bash

sudo mkdir /mnt/bb-orangefs


sudo mount -t pvfs2 tcp://node4:3334/orangefs /mnt/bb-orangefs
