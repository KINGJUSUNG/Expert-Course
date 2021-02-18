#!/bin/bash

# 전화번호부를 저장하기 위한 파일을 하나 생성합니다.
touch ~/.phonebook

register() {
	clear
	echo "#전화번호 등록#"
	read -p "이름 입력 : " name

	if [ -z "$name" ]; then
		echo "이름을 입력하지 않았습니다. 메뉴로 돌아갑니다!"
		read
		return
	fi

	result=$(grep "$name" ~/.phonebook)
	if [ -n "$result" ]; then
		echo "이미 등록된 이름입니다."
		read
		return
	fi
	
	read -p "전화번호 입력: " tel
	echo "$name $tel" >> ~/.phonebook
	echo "정상 등록되었습니다."
}

search() {
	clear
	read -p "이름 입력 : " name

	if [ -z "$name" ]; then
		echo "이름을 입력하지 않았습니다. 메뉴로 돌아갑니다!"
		read
		return
	fi

	result=$(grep "$name" ~/.phonebook)

	if [ -z "$result" ]; then
		echo "등록된 이름이 없습니다."
		read
		return
	fi

	echo "결과 : $result"
}

delete() {
	clear
	read -p "이름 입력 : " name

	if [ -z "$name" ]; then
		echo "이름을 입력하지 않았습니다. 메뉴로 돌아갑니다!"
		read
		return
	fi

	result=$(grep "$name" ~/.phonebook)

	if [ -z "$result" ]; then
		echo "등록된 이름이 없습니다."
		read
		return
	fi

	grep -v "$name" ~/.phonebook > ~/.phonebook_new
	rm ~/.phonebook
	mv ~/.phonebook_new ~/.phobebook

	echo "삭제되었습니다." 
	read
}


# 메뉴 출력 함수
display_menu() {
	clear
	echo "#전화번호부 프로그램#"
	echo "1. 등록"
	echo "2. 검색"
	echo "3. 삭제"
	echo "---------------------"
	echo -n "입력(0. 종료): "
	read
}

while true; do
	display_menu
	case $REPLY in
		0) 	echo "프로그램을 종료합니다."
			exit 0;;
		1)	register;;
		2)	search;;
		3)	delete;;
		*) 	echo "잘못 입력하셨습니다." 
			read;;
	esac
done
