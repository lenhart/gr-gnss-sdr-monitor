#!/bin/bash


# cleanup used resources and kill child processes
function cleanup {
	echo ">>> cleaning up"
	#test -e "$fifo_name" && rm "$fifo_name"
	
	kill -- -$$ # kill subprocesses
	exit 0
}
# catch sigint
trap cleanup SIGINT


python3 -m gr_receiver &

gnss-sdr --config-file=gnss-file-source.conf &

