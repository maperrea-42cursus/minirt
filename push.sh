git add -A
git status -s
echo "do you wish to push? [y/n]:"
select yn in "y" "n"; do
	case $yn in
		y ) echo "enter commit message:"
			read $message
			git commit -m "message"
			git push github master
			;;
		n ) exit;;
	esac
done
