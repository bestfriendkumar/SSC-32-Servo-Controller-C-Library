CC = gcc
CFLAGS = -Wall -std=c99 -g
OBJECTS = servo.o radio.o
SOURCES = servo.c radio.c
TEST_OBJECTS = servo.o servoInteract.o
TEST_SOURCES = servo.c servoInteract.c
REQUIREMENT_OBJECTS = servo.o requirement_tracker.o
REQUIREMENT_SOURCES = servo.c requirement_tracker.c
HEADERS = servo.h

servoInteract: $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

servo.o: $(HEADERS)

servoInteract.o: $(HEADERS) servo.o


requirement_tracker: $(REQUIREMENT_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

requirement_tracker_cov: $(REQUIREMENT_SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(COVFLAGS) $^ -o $@

requirement_tracker.o: $(HEADERS) servo.o

clean:
	rm -f servoInteract
	rm -f requirement_tracker
	rm -f *.o
	rm -f *.gc*