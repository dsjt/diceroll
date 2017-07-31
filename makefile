CC=/usr/bin/cc
CPP=/usr/bin/cpp
a.out: prog1.c
	$(CC) -framework GLUT -framework OpenGL prog1.c

b.out: prog2.c
	$(CC) -framework GLUT -framework OpenGL -mmacosx-version-min=10.8 prog2.c -o b.out

c.out : dice.c
	$(CC) -framework GLUT -framework OpenGL -mmacosx-version-min=10.8 dice.c -o c.out -lm

d.out : dice.cpp
	c++ -framework GLUT -framework OpenGL -mmacosx-version-min=10.8 dice.cpp -o d.out -lm
