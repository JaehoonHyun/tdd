#!/bin/bash

# ubuntu 18.04
echo "deb https://repos.influxdata.com/ubuntu bionic stable" | sudo tee /etc/apt/sources.list.d/influxdb.list
sudo curl -sL https://repos.influxdata.com/influxdb.key | sudo apt-key add -
sudo apt-get update
sudo apt-get install -y influxdb

#systemctl enable
sudo systemctl enable --now influxdb
sudo systemctl is-enabled influxdb
systemctl status influxdb

#ufw ubuntu firewall
sudo apt-get install ufw -y
sudo ufw enable
sudo ufw allow 8086/tcp

# $ sudo vim /etc/influxdb/influxdb.conf 
# [http]
#  auth-enabled = true

