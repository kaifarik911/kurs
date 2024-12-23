# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Каталоги и файлы
SRCDIR = .
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)

# Файлы и библиотеки
MAIN_OBJ = data.o error.o client.o terminal.o main.o
UNIT_OBJ = data.o error.o client.o terminal.o unit.o

TARGET_MAIN = client
TARGET_UNIT = unit

LDFLAGS = -lcryptopp -lUnitTest++

# Правила
all: $(TARGET_MAIN) $(TARGET_UNIT) clean

$(TARGET_MAIN): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lcryptopp

$(TARGET_UNIT): $(UNIT_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

.PHONY: all clean
