#/bin/bash

LWH=/user/lwh1990

mpicc -I/users/lwh1990/ROSS/install/include  -I/users/lwh1990/codes-0.6.0/install/include  -L/users/lwh1990/ROSS/install/lib -L/users/lwh1990/codes-0.6.0/install/lib    bb.c  -lROSS -lm -lcodes  -o  bb

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/users/lwh1990/ROSS/install/lib:/users/lwh1990/codes-0.6.0/install/lib

./bb --codes-config=bb.conf

