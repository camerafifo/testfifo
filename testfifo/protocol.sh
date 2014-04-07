#!/bin/bash

declare -a client_request
client_request[0]="set_state"
client_request[1]="get_state"
client_request[2]="set_color"
client_request[3]="get_color"
client_request[4]="set_rate"
client_request[5]="get_rate"

set_state()
{
	printf "set-led-state $2\n">"$fifo_name.$1"	
}

get_state()
{
	printf "get-led-state \n">"$fifo_name.$1"
}

set_color()
{
	printf "set-led-color $2\n">"$fifo_name.$1"
}

get_color()
{
	printf "get-led-color \n">"$fifo_name.$1"
}

set_rate()
{
	printf "set-led-rate $2\n">"$fifo_name.$1"
}

get_rate()
{
	printf "get-led-rate \n">"$fifo_name.$1"
}
