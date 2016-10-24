#!/bin/sh

exec 2>error.log

sudo sh load.sh
echo "#1 n = 1"\\r
echo 1 > /dev/calc_number
result=$(cat /dev/calc_result)
if [ "$result" -eq "1" ];
then
    echo "OK. fib(1) == $result"\\r
else
    echo "ERROR. fib(1) != $result"\\r
fi


echo "#2 n = 2"\\r
echo 2 > /dev/calc_number
result=$(cat /dev/calc_result)
if [ "$result" -eq "1" ];
then
    echo "OK. fib(2) == $result"\\r
else
    echo "ERROR. fib(2) != $result"\\r
fi


echo "#3 n = 3"\\r
echo 3 > /dev/calc_number
result=$(cat /dev/calc_result)
if [ "$result" -eq "2" ];
then
    echo "OK. fib(3) == $result"\\r
else
    echo "ERROR. fib(3) != $result"\\r
fi



echo "#4 n = 10"\\r
echo 10 > /dev/calc_number
result=$(cat /dev/calc_result)
if [ "$result" -eq "55" ];
then
    echo "OK. fib(10) == $result"\\r
else
    echo "ERROR. fib(10) != $result"\\r
fi


echo "#5 n = -13"\\r
echo -13 > /dev/calc_number
result=$(cat /dev/calc_result)
echo "fib(-13) == $result"\\r
if [ "$result" -eq "-233" ];
then
    echo "OK. fib(-13) == $result"\\r
else
    echo "ERROR. fib(-13) != $result"\\r
fi


sudo sh unload.sh
