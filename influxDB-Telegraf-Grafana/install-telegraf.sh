#!/bin/bash

sudo apt-get install -y telegraf

# sudo vi /etc/telegraf/telegraf.conf
# [[outputs.influxdb]]
# urls = ["http://127.0.0.1:8086"]
# database = "telegraf"