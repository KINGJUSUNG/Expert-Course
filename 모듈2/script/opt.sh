#!/bin/bash

# ./a.sh -a -b -c

# while [ -n "$(echo $1 | grep '-')" ]; do	# while ($1)
# 	case $1 in
# 		-a) echo 'option a';;
# 		-b) echo 'option b';;
# 		-c) echo 'option c';;
# 		*) echo 'usage: a.sh [-a] [-b] [-c]'
# 			exit 1;;
# 	esac
# 	shift
# done


# getopts: 계속 처리해야할 옵션이 있으면 종료코드를 0으로 설정하고
# 처리할 옵션이 없으면 종료 코드를 1로 설정함
# 첫번째 : => 해당하지 않는 옵션이 들어올 시 에러출력 안함
# 두번째 : => 특정 옵션에 대한 인자처리
while getopts ":ab:c" opt; do
	case "$opt" in
		a) echo "option a";;
		b) echo "option b $OPTARG";;
		c) echo "option c";;
		\?) echo "usage: a.sh [-a] [-b filename] [-c]" # 다른 옵션이 들어온 경우, ?로 설정됨
			exit 1;;
	esac
done

