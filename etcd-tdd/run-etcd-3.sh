#!/bin/bash

etcd --name etcd-03 \
--initial-advertise-peer-urls http://172.19.0.4:2380 \
--listen-peer-urls http://172.19.0.4:2380 \
--listen-client-urls http://172.19.0.4:2379,http://127.0.0.1:2379 \
--advertise-client-urls http://172.19.0.4:2379 \
--initial-cluster-token "etcd-cluster-1" \
--initial-cluster etcd-01=http://172.19.0.2:2380,etcd-02=http://172.19.0.3:2380,etcd-03=http://172.19.0.4:2380 \
--initial-cluster-state new