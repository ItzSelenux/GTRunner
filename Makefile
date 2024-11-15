VERSION := $(shell cat VERSION)

CC = cc
CFLAGS = `pkg-config --cflags gtk+-3.0 ayatana-appindicator3-0.1` -Dpver=\"$(VERSION)\" $(FLAGS)
LIBS = `pkg-config --libs gtk+-3.0 ayatana-appindicator3-0.1` -Dpver=\"$(VERSION)\" $(FLAGS)

SRC = gtrunner.c
OBJ = $(SRC:.c=.o)
EXE = gtrunner

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

debug: $(SRC)
	$(CC) $(CFLAGS) -g $^ -o debug $(LIBS)

test: $(EXE)
	./$(EXE)

clean:
	rm -f $(OBJ) $(EXE) debug

install: $(EXE)
	install -Dm755 $(EXE) /usr/local/bin/$(EXE)
	install -Dm755 gtrunner.desktop /usr/local/share/applications/gtrunner.desktop

uninstall:
	rm -f /usr/local/bin/$(EXE)
	rm -f /usr/local/share/applications/gtrunner.desktop
