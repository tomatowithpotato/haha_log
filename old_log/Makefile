SOURCE_DIR = .

SOURCE_FILES = $(wildcard $(SOURCE_DIR)/*.cpp)
SOURCE_FILES += $(wildcard $(SOURCE_DIR)/*/*.cpp)

INCLUDE_DIR = -I .

old_log: test_old_log.cc $(SOURCE_FILES)
	g++ -std=c++2a $(INCLUDE_DIR) test_old_log.cc $(SOURCE_FILES) -lpthread -luuid -o oldLogdTest