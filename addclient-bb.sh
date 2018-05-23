#!/bin/bash

sudo mkdir /mnt/orangefsbb


sudo mount -t pvfs2 tcp://server4:3334/orangefs /mnt/orangefsbb
