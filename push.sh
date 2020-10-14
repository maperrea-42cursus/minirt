#!/bin/zsh
git add -A
git status -s
echo -n "do you wish to push? [y/n]:"
read yn
case $yn in
	y ) echo -n "enter commit message:"
		read message
		git commit -m "$message"
		git push github master
		;;
	n ) exit;;
esac
