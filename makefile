TARGET = yt-grabber-tui

CXX = g++
CXXFLAGS = -Wall -O2 -Iinclude
LDFLAGS = -pthread
LIBS = -Wl,-Bstatic \
       -lboost_system -lboost_filesystem -lboost_thread \
       -lboost_program_options -lboost_regex \
       -Wl,-Bdynamic \
       -lftxui-component -lftxui-dom -lftxui-screen \
       -lfmt

SRC_DIR = src
OBJ_DIR = obj
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)
	@echo "Сборка завершена успешно!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)