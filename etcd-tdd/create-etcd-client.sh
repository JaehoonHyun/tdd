#!/bin/bash

docker run --rm -it --name etcd-client --net mynet --ip 172.19.0.5 -v $(pwd):/host etcd-ubuntu:16.04