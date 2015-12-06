CC = gcc

FLAGS = -Wall -pedantic 

default: SantaChooser SecretSanta

SantaChooser: SantaChooser.c
	$(CC) $(FLAGS) -o SantaChooser SantaChooser.c

SecretSanta: SecretSanta.c
	$(CC) $(FLAGS) -o SecretSanta SecretSanta.c

list: SantaChooser
	./SantaChooser

tell: SecretSanta
	./SecretSanta
clean:
	rm SantaChooser
	rm SecretSanta
	rm SecretList.txt
