#!/bin/bash
#@author Virgile Retault
container_name=compiler
if [ "$( docker container inspect -f '{{.State.Running}}' $container_name 2>/dev/null )" != "true" ]; then	
	echo "STARTING DOCKER CONTAINER."
	docker run --rm -dit --name $container_name -v `pwd`:/src -w /src --hostname ev3dev ev3cc
	docker exec $container_name bash -c 'cd ev3dev-c/source/ev3/;make;make install'
	docker exec $container_name bash -c "cd ev3dev-c;pwd"
fi
