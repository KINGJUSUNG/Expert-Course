#!/bin/bash

foo() {
	echo "매개변수 개수: $#"
	for arg in $@; do
		echo "$arg"
	done
}

foo hello world goodbye


name1=a
name2=b
foo $name1 $name2


# 이런식으로 함수의 리턴값을 캐치
foo() {
	echo 10
}

ret=$(foo)
echo "ret: $ret"
