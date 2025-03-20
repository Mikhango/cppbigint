# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Файлы и исполняемые файлы
SOURCES = tests.cpp getpihundred.cpp
TARGETS = test pi

# Компиляция всех файлов при вызове "make"
all: $(TARGETS)

test: tests.o
	$(CXX) $(CXXFLAGS) -o test tests.o
	./test  # Запуск test

pi: getpihundred.o
	$(CXX) $(CXXFLAGS) -o pi getpihundred.o
	./pi  # Запуск pi

# Компиляция .cpp в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f test pi *.o

.PHONY: all clean test pi
