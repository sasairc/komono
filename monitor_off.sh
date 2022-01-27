#!/bin/sh

xset q | grep 'Monitor is On' > /dev/null && xset dpms force off
