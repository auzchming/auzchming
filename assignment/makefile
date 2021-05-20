CC = gcc
CFLAGS = -Wall -ansi -pedantic -Werror
OBJ = laserTank.o graph.o movement.o lasergopewpew.o enemylasergopewpew.o newSleep.o 
EXEC = laserTank
$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)



laserTank.o : laserTank.c graph.c movement.c lasergopewpew.c enemylasergopewpew.c
	$(CC) -c laserTank.c  $(CFLAGS)

graph.o : graph.c movement.c
	$(CC) -c graph.c $(CFLAGS)

movement.o : movement.c
	$(CC) -c movement.c $(CFLAGS)

lasergopewpew.o : lasergopewpew.c movement.c newSleep.c
	$(CC) -c lasergopewpew.c $(CFLAGS)

enemylasergopewpew.o : enemylasergopewpew.c movement.c newSleep.c
	$(CC) -c enemylasergopewpew.c $(CFLAGS)
	
newSleep.o : newSleep.c newSleep.h
	$(CC) -c newSleep.c $(CFLAGS)


clean:
	rm -f $(EXEC) $(OBJ) 
