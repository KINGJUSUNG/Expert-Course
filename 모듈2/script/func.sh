# 함수의 정의 1
# fuction 함수명 {
# 	commands...
# }

function foo {
	echo "foo()"
}

# 함수의 정의 2
# 함수명() {
# 	commands...
# }

hoo() {
	echo "hoo()"
}

# 주의할 점 1. 함수 정의 시, 서로 다른 행에서 작성해야 함
# hoo() { echo "hoo()" }

# 주의할 점 2. 함수 내에서는 반드시 1개 이상의 명령어가 존재해야함
# 주석만 포함되어 있어도 안됨
