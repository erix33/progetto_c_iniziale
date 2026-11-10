CC = clang
CFLAGS = -Wall -Wextra -std=gnu17 -Iinclude -g
LDFLAGS = 

TARGET = build/programma.exe
OBJ = build/main.o build/funzioni.o

# --- RILEVAMENTO AUTOMATICO SISTEMA OPERATIVO ---
ifeq ($(OS),Windows_NT)
    RM = del /Q
    CLEAN_PATH = build\*.o build\*.exe 2>nul
    MKDIR = if not exist build mkdir build
else
    RM = rm -rf
    CLEAN_PATH = build/*.o build/*.exe build
    MKDIR = mkdir -p build
endif

.PHONY: all asan clean

# Target 1: Compilazione Standard (senza ASan, perfetto per Valgrind)
all: build $(TARGET)

# Target 2: Compilazione per Sviluppo Rapido (con ASan attivo)
asan: CFLAGS += -fsanitize=address
asan: LDFLAGS += -fsanitize=address
asan: clean build $(TARGET)

build:
	$(MKDIR)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET)

build/main.o: src/main.c include/funzioni.h
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/funzioni.o: src/funzioni.c include/funzioni.h
	$(CC) $(CFLAGS) -c src/funzioni.c -o build/funzioni.o

clean:
	$(RM) $(CLEAN_PATH)