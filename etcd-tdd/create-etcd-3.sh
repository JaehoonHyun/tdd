#!/bin/bash

docker run --rm -it --name etcd-3 --net mynet --ip 172.19.0.4 -v $(pwd):/host etcd-ubuntu:16.04