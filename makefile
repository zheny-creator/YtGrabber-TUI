TARGET = yt-grabber-tui

CXX = g++
CXXFLAGS = -Wall -O2 -Iinclude
LDFLAGS = -pthread

BASE_LIBS = -lftxui-component -lftxui-dom -lftxui-screen

LIBS_GLIBC = -Wl,-Bstatic \
             -lboost_process -lboost_filesystem -lboost_thread \
             -lboost_program_options -lboost_regex \
             -Wl,-Bdynamic -lfmt \
             -Wl,-rpath,'$$ORIGIN/libs'

LIBS_ALPINE = -lboost_process -lboost_filesystem -lboost_thread \
              -lboost_program_options -lboost_regex \
              -lfmt \
              -Wl,-rpath,'$$ORIGIN/libs'

LIBS_WINDOWS_STATIC = -L/ucrt64/lib \
                      -Wl,-Bstatic \
                      -lboost_system -lboost_process -lboost_filesystem -lboost_thread \
                      -lboost_program_options -lboost_regex \
                      -Wl,-Bdynamic -lfmt -lws2_32 -lgdi32

LIBS_GLIBC_DYNAMIC = -lboost_process -lboost_filesystem -lboost_thread \
                     -lboost_program_options -lboost_regex \
                     -lfmt \
                     -Wl,-rpath,'$$ORIGIN/libs'

SRC_DIR = src
OBJ_DIR = obj
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(TARGET)

alpine: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(TARGET) $(BASE_LIBS) $(LIBS_ALPINE)

dynamic: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(TARGET) $(BASE_LIBS) $(LIBS_GLIBC_DYNAMIC)

windows: CXXFLAGS += -I/ucrt64/include -D_WIN32_WINNT=0x0602
windows: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(TARGET) $(BASE_LIBS) $(LIBS_WINDOWS_STATIC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(TARGET) $(BASE_LIBS) $(LIBS_GLIBC)

clean:
	@rm -rf $(OBJ_DIR) $(TARGET)