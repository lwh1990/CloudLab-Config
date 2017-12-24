# CloudLab Configuration
To ease the build!

## ssh config
```
cp id_rsa_s ~/.ssh/id_rsa
chmod 600 ~/.ssh/id_rsa
for((i=1;i<4;i++));do scp /users/lwh1990/.ssh/id_rsa server$i:/users/lwh1990/.ssh/  ;done
for((i=0;i<4;i++));do scp /users/lwh1990/.ssh/id_rsa node$i:/users/lwh1990/.ssh/  ;done
```

## Build OrangFS 
```
# server0
./hdd.sh
./buildorangefs.sh
```

## Add I/O server 
```
# serveri
./hdd.sh
./addserver.sh i
```

## Add compute node 
```
# nodei
./addclient.sh
./installbasic.sh
./installtest.sh (node0)
```
## Add burst buffer node 
```
# nodei
./ssd.sh
./addclient.sh
./installbasic.sh
```

## bb node build orangefs
```
# node4 server
./buildorangefs-bb.sh
# node5-7 server
./addserver-bb.sh
# node0-7 client
./addclient-bb.sh
```

