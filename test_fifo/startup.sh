#!/bin/bash

## script to start test environment for developing a distributed meaconer
# current state: start gnss-sdr and collect output somewhere usable.


# cleanup used resources and kill child processes
function cleanup {
	echo ">>> cleaning up"
	#test -e "$fifo_name" && rm "$fifo_name"
	
	kill -- -$$ # kill subprocesses
	exit 0
}
# catch sigint
trap cleanup SIGINT


# start gnss-sdr
gnss-sdr --config-file=gnss-file-source-deterministic.conf

# mkfifo fifo.fifo
# to fifo nc -lu >> fifo.fifo
