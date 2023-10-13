run:
	gcc steam_carving.c -o steam_carving -Wall -Wextra -Wvla -Werror -fsanitize=address,undefined -lm
	./steam_carving ./images/boat.png ./out/result.png
	eog ./out/result.png