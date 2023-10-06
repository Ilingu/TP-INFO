run5: build5
	./exo5 -imax 50 -n 1000 > mandelbrot.pgm

build5:
	gcc exo5.c -o exo5 -Wall -Wextra -Wvla -Werror -fsanitize=address,undefined
