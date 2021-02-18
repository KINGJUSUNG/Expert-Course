#!/bin/bash

# trap "echo 'CTRL +C'" SIGINT
# 
# for ((i = 0; i < 10; i++)); do
# 	echo "."
# 	sleep 1
# done


# sig_handler() {
# 	echo "sig_handler()"
# }


SIGINT_handler() {
	echo "CTRL + C"
}
trap SIGINT_handler SIGINT


SIGQUIT_handler() {
	echo "CTRL + \\"
}
trap SIGQUIT_handler SIGQUIT

for ((i = 0; i < 10; i++)); do
	echo "."
	sleep 1
done

trap -- SIGINT # 해당 시그널을 삭제

for ((i = 0; i < 10; i++)); do
	echo "."
	sleep 1
done
