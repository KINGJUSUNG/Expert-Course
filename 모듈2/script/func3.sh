fact() {
	if (($1 <= 1)); then
		echo 1
	else
		local temp=$(($1-1))
		local result=$(fact $temp)
		echo $((result * $1))
	fi
}

echo $(fact 5)
