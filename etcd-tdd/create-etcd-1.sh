#!/bin/bash

docker run --rm -it --name etcd-1 --net mynet --ip 172.19.0.2 -v $(pwd):/host etcd-ubuntu:16.04
