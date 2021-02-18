#!/bin/bash

str="global"

# func() {
# 	local str="local"
# 	echo $str
# }
# echo $str
# 
# func
# read
# echo $str


# func() {
# # 	str="local"	# 함수 내에서 local없이 생성된 변수는 전역변수로 취급됨
# 	echo $str
# }
# 
# echo $str
# func
# read
# echo $str


# bash에서 함수는 진짜 함수가 아니므로 매개변수를 가질 수 없음
# foo(x, y) {
# }

foo() {
	# 전달된 인자는 위치 매개변수에 저장됨
	echo $1
	echo $2
}

#함수 호출 시, 인자 전달은 명령행에서 인자를 전달하는 것과 동일하게 수행하면 됨


