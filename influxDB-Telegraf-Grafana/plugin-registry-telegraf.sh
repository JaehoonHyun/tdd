#!/bin/bash

sudo cp ./plugin-telegraf.conf /etc/telegraf/telegraf.d/ 
sudo systemctl restart telegraf.service