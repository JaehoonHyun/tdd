#!/bin/bash

apt-get update
apt-get install curl -y
apt-get install wget -y
wget https://github.com/coreos/etcd/releases/download/v3.3.9/etcd-v3.3.9-linux-amd64.tar.gz
tar xvfz etcd-v3.3.9-linux-amd64.tar.gz
cd etcd-v3.3.9-linux-amd64

cp etcd etcdctl /usr/local/bin/
echo $PATH

etcd --version