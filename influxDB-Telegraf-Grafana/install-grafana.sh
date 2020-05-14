#!/bin/bash

wget -q -O - https://packages.grafana.com/gpg.key | sudo apt-key add -
sudo add-apt-repository "deb https://packages.grafana.com/oss/deb stable main"
sudo apt-get update
# apt-cache policy grafana
sudo apt-get install -y grafana

# service 
sudo systemctl enable grafana-server
sudo systemctl start grafana-server
sudo systemctl status grafana-server