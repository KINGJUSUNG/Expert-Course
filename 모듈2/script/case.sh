#!/bin/bash

echo "
a. 짜장면
b. 탕수육
c. 짬뽕
q. 종료"

read -p "*메뉴를 선택해주세요: "

case $REPLY in
	q|Q) exit 0;;
	a|A) echo "a";;
	b|B) echo "b";;
	c|C) echo "c";;
	*) echo "잘못입력"
		exit;;
esac
