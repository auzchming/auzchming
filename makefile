CC = gcc
CFLAGS = -Wall -ansi -pedantic -Werror -Iheaders
OBJ = laserTank.o graph.o movement.o lasergopewpew.o enemylasergopewpew.o newSleep.o linkedlist.o log.o
EXEC = laserTank
$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

laserTank.o : laserTank.c graph.c movement.c lasergopewpew.c enemylasergopewpew.c linkedlist.c log.c
	$(CC) -c laserTank.c  $(CFLAGS)

graph.o : graph.c movement.c linkedlist.c log.c 
	$(CC) -c graph.c $(CFLAGS)

movement.o : movement.c
	$(CC) -c movement.c $(CFLAGS)

lasergopewpew.o : lasergopewpew.c movement.c newSleep.c linkedlist.c log.c 
	$(CC) -c lasergopewpew.c $(CFLAGS)

enemylasergopewpew.o : enemylasergopewpew.c movement.c newSleep.c linkedlist.c log.c 
	$(CC) -c enemylasergopewpew.c $(CFLAGS)
	
newSleep.o : newSleep.c 
	$(CC) -c newSleep.c $(CFLAGS)

log.o  : log.c
	$(CC) -c log.c $(CFLAGS)

linkedlist.o : linkedlist.c
	$(CC) -c linkedlist.c $(CFLAGS)
clean:
	rm -f $(EXEC) $(OBJ) 
