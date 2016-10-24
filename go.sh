#!/bin/bash

sudo sh load.sh
#`dmesg | grep -m 1 "mknod" | awk -F "'" {'print $2'}`

function check {
    echo $1 > /dev/first
    echo $2 > /dev/operator
    echo $3 > /dev/second
	result=$(cat /proc/result)
    if [ "$4" == "$result" ]; then
        echo "True!"
    else
        echo "False!"
	echo "Expected:"
	echo "$4"
	echo "Getted:"
	echo "$result"
    fi
}

check 3 + 2 "5"
check 3 / 0 "NaN"
check 4 + 7 "11"
check 4 - 10 "-6"
check 4 / 2 "2"
check 2 p 2 "4"
check 11 p 11 "121"

sudo sh unload.sh
