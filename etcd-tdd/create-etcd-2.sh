#!/bin/bash

docker run --rm -it --name etcd-2 --net mynet --ip 172.19.0.3 -v $(pwd):/host etcd-ubuntu:16.04