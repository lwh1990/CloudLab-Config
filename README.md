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
./buildorangefs.sh
```

## Add I/O server 
```
# serveri
./addserver.sh i
```

## Add compute node 
```
# nodei
./addclient.sh
./installbasic.sh
./installtest.sh (node0)
```
## Add burst buffer server
```
#first bbserver
./buildorangefs-bb.sh
#other bbservers
./addserver-bb.sh
#add client
./addclient-bb.sh
```
