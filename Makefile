all:
	docker run --rm -e PLAT=manylinux1_x86_64 -v .:/io quay.io/pypa/manylinux1_x86_64:latest /io/build-wheels.sh
