all: BuildImage

OBJECT_DIRECTORY = ../../Output

SOURCE_FILES = $(wildcard ./*.cpp)
HEADER_FILES = $(wildcard ./*.h)

BuildImage:
	@echo build merger

	mkdir -p $(OBJECT_DIRECTORY)
	g++ $(HEADER_FILES) $(SOURCE_FILES) -o $(OBJECT_DIRECTORY)/Merger