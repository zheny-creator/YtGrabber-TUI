TARGET = yt-grabber-tui

CXX = g++
CXXFLAGS = -Wall -O2 -Iinclude -static -static-libstdc++ -static-libgcc
LDFLAGS = -pthread
LIBS = -lboost_system -lboost_filesystem -lboost_thread \
       -lboost_program_options -lboost_regex -lfmt
SRC_DIR = src
OBJ_DIR = obj
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LIBS)
	@echo "✅ Сборка завершена успешно!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f yt-grabber-tui
	rm -r obj
