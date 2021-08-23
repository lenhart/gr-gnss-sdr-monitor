#!/bin/bash
# collect data from gnss-sdr and dump serialized output to files

# cleanup used resources and kill child processes
function cleanup {
	kill -- -$$ # kill subprocesses
	exit 0
}
# catch sigint
trap cleanup SIGINT

nc -lu 1234 > monitor.bat &
nc -lu 1233 > pvt.bat &
gnss-sdr --config_file=gnss-file-source.conf

# keep open to let programs finish
read -p "press key to stop" -n1 -s -r

cleanup
