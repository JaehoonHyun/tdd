#!/bin/bash

set -e

#2379로 접근하니깐 proxy 역할을 하는듯
echo "etcd helath check"
curl http://etcd-1:2379/health
curl http://etcd-2:2379/health
curl http://etcd-3:2379/health
echo

echo "etcd status check"
etcdctl --endpoints http://etcd-1:2379 cluster-health
# member 11e7446b98dff567 is healthy: got healthy result from http://172.19.0.3:2379
# member 26e0dea6e9bb9338 is healthy: got healthy result from http://172.19.0.2:2379
# member db5f35f9429846f7 is healthy: got healthy result from http://172.19.0.4:2379
echo

echo "etcdctl member list"
etcdctl --endpoints http://etcd-1:2379 member list
# 11e7446b98dff567: name=etcd-02 peerURLs=http://172.19.0.3:2380 clientURLs=http://172.19.0.3:2379 isLeader=false
# 26e0dea6e9bb9338: name=etcd-01 peerURLs=http://172.19.0.2:2380 clientURLs=http://172.19.0.2:2379 isLeader=false
# db5f35f9429846f7: name=etcd-03 peerURLs=http://172.19.0.4:2380 clientURLs=http://172.19.0.4:2379 isLeader=true
echo

# keys/{key} -XPUT -d value="{data}"
# post 메소드 시, 키가 또 존재하면 에러 뱉음
echo "etcd update and create key/value"
curl http://etcd-1:2379/v2/keys/message -XPUT -d value="hello world"
curl http://etcd-1:2379/v2/keys/message -XPUT -d value="My is jaehoon"
curl http://etcd-1:2379/v2/keys/foos -XPUT -d value="bar"
curl http://etcd-1:2379/v2/keys/foos -XPUT -d value="kek"
echo

echo "etcd read key"
curl http://etcd-1:2379/v2/keys/foos
echo 

echo "etcd delete key"
curl http://etcd-1:2379/v2/keys/foos -XDELETE
echo
