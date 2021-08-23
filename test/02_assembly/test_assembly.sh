#!/bin/bash
# shell script to test the gr-assembly program. Takes a deserialized output from gr and 
# expects a deserialized file. we can save data by converting..

infile="monitor.bat"
deser_file="monitor_deserialized.log" # intermediate file
protofile="gnss_synchro.proto"
acc=""

# cleanup used resources and kill child processes
function cleanup {
	echo "cleanup"
	
    if [[ -f "$deser_file" ]]; then
        rm "$deser_file"
    fi
    
	kill -- -$$ # kill subprocesses
	exit 0
}
# catch sigint
trap cleanup SIGINT


if [ ! -f "$infile" ]; then 
    echo "$infile does not exist"
fi
if [ ! -f $protofile ]; then
    echo "$protofile does not exist"
fi

# decode file (saves space)
echo "Deserializing input"

protoc --decode gnss_sdr.Observables "$protofile" < "$infile" > "$deser_file"
echo "Done"

# read file and accumulate one observable message at a time. If complete, serialize and send via nc
while read -r line; do
    acc="$acc\n$line"
    if [[ "$line" == "}" ]]; then
        echo -e "$acc" | protoc --encode="gnss_sdr.Observables" "$protofile" | timeout 0.1 nc -u 127.0.0.1 1234
        acc=""
    fi
done < "$deser_file"

cleanup
##================f
# prior attempts which did not work:
# grep -A25 "observable" test_data/monitor_deserialized.log | protoc --encode="gnss_sdr.Observables" gr-gnsssdr_mod/lib/gnss_synchro.proto | nc -u 127.0.0.1 1234
#cat test_data/monitor_deserialized.log | xargs -L 24 | 
