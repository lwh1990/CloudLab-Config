# CloudLab Configuration
To ease the build!

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
./add addserver.sh i
```

## Add compute node 
```
# nodei
./addclient.sh
./installbasic.sh
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

