make
if [[ $? -ne 0 ]]; then
	exit
fi
if [[ ! -n $1 ]]; then
	./minirt maps/map.rt
else
	./minirt $*
fi
