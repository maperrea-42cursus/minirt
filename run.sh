make
if [[ $? -ne 0 ]]; then
	exit
fi
if [[ ! -n $1 ]]; then
	screen -d -m ./minirt maps/map.rt
else
	screen -d -m ./minirt $*
fi
