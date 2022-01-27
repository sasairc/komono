#!/bin/sh

xset q | grep 'Monitor is Off' > /dev/null && xset dpms force on
