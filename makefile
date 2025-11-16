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
              
LIBS_WINDOWS_DYNAMIC = -lboost_process-mt -lboost_filesystem-mt -lboost_thread-mt \
                       -lboost_program_options-mt -lboost_regex-mt \
                       -lfmt

LIBS_GLIBC_DYNAMIC = -lboost_process -lboost_filesystem -lboost_thread \
                     -lboost_program_options -lboost_regex \
                     -lfmt \
                     -Wl,-rpath,'$$ORIGIN/libs'

SRC_DIR = src
OBJ_DIR = obj
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: $(TARGET)

alpine: LDFLAGS += $(LIBS_ALPINE)
alpine: $(TARGET)-musl
	@mv $(TARGET)-musl yt-grabber-tui

dynamic: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(TARGET) $(BASE_LIBS) $(LIBS_GLIBC_DYNAMIC)

windows: CXXFLAGS += -D_WIN32_WINNT=0x0602
windows: LDFLAGS += $(LIBS_WINDOWS_DYNAMIC)
windows: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(TARGET) $(BASE_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(TARGET) $(BASE_LIBS) $(LIBS_GLIBC)

clean:
	@rm -rf $(OBJ_DIR) $(TARGET) $(TARGET)-musl