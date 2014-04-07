#!/bin/bash
source protocol.sh

action_arr=(--setled --getled)
target_arr=(--state --color --rate)
ntgt_arr=(1 0 1 0 1 0)

#state_val_set=(on off)
#color_val_set=(red green blue)
#rate_val_set=(0 1 2 3 4 5)

echo "Request Id: $BASHPID"

clientId=$BASHPID

if [ $# -lt  2 ]; then
        echo "Passed arguments are invalid"
        exit 0
fi

action_id=0
target_id=0
ntgt_id=0
nvalid_arg=0

for arg in "${action_arr[@]}"; do
    if [[ $arg = $1 ]]; then
        echo "Action name is $arg"
        break
    fi
    ((action_id++))
done

if [ "$action_id" -eq "${#action_arr[*]}" ]; then
	echo "Action is invalid"
	exit 0
fi

for arg in "${target_arr[@]}"; do
    if [[ "$arg" = "$2" ]]; then
        echo "Target name is $arg"
        break
    fi
    ((target_id++))
done

if [ "$target_id" -eq "${#target_arr[*]}" ]; then
	echo "Target is invalid"
	exit 0
fi

let "ntgt_id = $target_id * ${#action_arr[*]} + $action_id"
let "nvalid_arg=${ntgt_arr[$ntgt_id]} + 2"

if [ $# -lt $nvalid_arg ]; then
        echo "Target value(s) is(are) invalid"
        exit 0
fi

let "client_request_id = $target_id * ${#action_arr[*]} + $action_id"

arg_values=""
fifo_name="cam_fifo"
index=3

while [ $index -le $# ]; do
    arg_values+=${!index}	 
    let "index++"    	
done

if [ -p $fifo_name ]; then
	echo "Connection is set"
	mkfifo "$fifo_name.$clientId"
	printf $clientId>$fifo_name
	${client_request[$client_request_id]} "$clientId" "$arg_values"        
	cat < "$fifo_name.$clientId"	
	rm "$fifo_name.$clientId"	
	exit 0
else
	echo "Connection is not set"
        exit 0
fi

exit 0


