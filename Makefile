main.o : main.c tetris.h
	gcc -c main.c -o main.o

initialization.o : initialization.c tetris.h
	gcc -c initialization.c -o initialization.o

game.o : game.c tetris.h
	gcc -c game.c -o game.o

checking.o : checking.c tetris.h
	gcc -c checking.c -o checking.o

highscore.o : highscore.c tetris.h
	gcc -c highscore.c -o highscore.o

exec : main.o initialization.o game.o checking.o highscore.o
	gcc *.o -o exec

clean :
	rm -f *.o
	rm exec
