# ===========================
# yt-grabber-tui — Makefile
# ===========================

TARGET = yt-grabber-tui

CXX = g++
CXXFLAGS = -Wall -O2 -Iinclude
LDFLAGS = -pthread

# Обычная (динамическая) сборка — добавлен boost_process
LIBS = -Wl,-Bstatic \
	-lftxui-component -lftxui-dom -lftxui-screen \
	-Wl,-Bdynamic \
	-lboost_system -lboost_filesystem -lboost_process -lboost_thread \
	-lboost_program_options -lboost_regex \
	-lfmt

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all clean release

STATIC ?=

ifeq ($(STATIC),1)
# Статическая сборка — только нужные компоненты Boost + fmt
LIBS = -Wl,-Bstatic \
	-lftxui-component -lftxui-dom -lftxui-screen \
	-lboost_process -lboost_filesystem -lboost_system \
	-lfmt \
	-Wl,-Bdynamic
LDFLAGS += -static-libstdc++ -static-libgcc
endif

all: $(TARGET)
	@echo "✅ Сборка завершена успешно!"

release:
	$(MAKE) STATIC=1 all
	@echo "🧱 Статическая сборка завершена успешно!"

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf $(OBJ_DIR)
	@echo "🧹 Очистка завершена!"
