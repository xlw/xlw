#!/bin/sh
python UpdateVersion.py > UpdateVersion.log
python UpdateClients.py
python UpdateDotNetClients.py

