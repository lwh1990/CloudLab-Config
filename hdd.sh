#!/bin/bash

yes | sudo mkfs.ext4 /dev/sdb
sudo mkdir /hdd
sudo mount -t ext4 /dev/sdb /hdd
sudo chmod a+rw /hdd
