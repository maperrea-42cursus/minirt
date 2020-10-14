#!/bin/zsh
git add -A
if [[ $1 == "-fast" ]]; then
	git status -s
	git commit -m "default fast commit message"
	git push github master
	exit
fi
git diff --cached --exit-code >/dev/null
if [[ $? -eq 0 ]]; then
	echo "No changes to be commited"
	exit
fi
git status -s
while true; do
	echo -n "do you wish to push? [y/n]: "
	read yn
	case $yn in
		Y | y )
			echo -n "enter commit message: "
			read message
			git commit -m "$message"
			git push github master
			exit;;
		N | n )
			exit;;
	esac
done
