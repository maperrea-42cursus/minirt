#!/bin/zsh
git add -A
git status -s
while true; do
	echo -n "do you wish to push? [y/n]: "
	read yn
	case $yn in
		Y | y ) echo -n "enter commit message: "
			read message
			git commit -m "$message"
			git push github master
			exit;;
		N | n ) exit;;
	esac
done
