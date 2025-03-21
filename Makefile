# Компилятор и флаги
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# Директории
SRC_DIR = src
BUILD_DIR = .

# Файлы и исполняемые файлы
SOURCES = $(SRC_DIR)/tests.cpp $(SRC_DIR)/getpihundred.cpp
OBJECTS = $(BUILD_DIR)/tests.o $(BUILD_DIR)/getpihundred.o
TARGETS = test pi

# Компиляция всех файлов при вызове "make"
all: $(TARGETS)

$(BUILD_DIR)/test: $(BUILD_DIR)/tests.o
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/test $(BUILD_DIR)/tests.o

$(BUILD_DIR)/pi: $(BUILD_DIR)/getpihundred.o
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/pi $(BUILD_DIR)/getpihundred.o

# Компиляция .cpp в .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Запуск программ (сначала проверяет, собран ли файл)
test: $(BUILD_DIR)/test
	./test

pi: $(BUILD_DIR)/pi
	./pi

# Очистка
clean:
	rm -f $(BUILD_DIR)/test $(BUILD_DIR)/pi $(BUILD_DIR)/*.o

.PHONY: all clean test pi