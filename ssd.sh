#!/bin/bash

yes | sudo mkfs.ext4 /dev/sdc
sudo mkdir /ssd
sudo mount -t ext4 /dev/sdc /ssd
sudo chmod a+rw /ssd
