CC=g++
FLAGS=-lgtest -lstdc++ -std=c++17
WCHECK=-Werror -Wall -Wextra
PROGRAM_NAME=3DViewer
COMPILATION_DIRECTORY=./build/
SOURCE_DIRECTORY=./src/
DIST_DIR = 3DViewer_dist

ifeq ($(shell uname), Linux)
APP=$(PROGRAM_NAME)
OPEN=xdg-open
EXEC=
LEAK_TEST=valgrind --leak-check=full 
else
APP=$(PROGRAM_NAME).app
OPEN=open
EXEC=open
LEAK_TEST=CK_FORK=no leaks -atExit -- 
endif

SOURCES = 	$(SOURCE_DIRECTORY)main.cc \
			$(SOURCE_DIRECTORY)view/custom_elements.cc \
			$(SOURCE_DIRECTORY)view/custom_elements.h \
			$(SOURCE_DIRECTORY)view/main_window.cc \
			$(SOURCE_DIRECTORY)view/main_window.h \
			$(SOURCE_DIRECTORY)view/rendering.cc \
			$(SOURCE_DIRECTORY)view/rendering.h \
			$(SOURCE_DIRECTORY)controller/controller.cc \
			$(SOURCE_DIRECTORY)controller/controller.h \
			$(SOURCE_DIRECTORY)model/3d_model.cc \
			$(SOURCE_DIRECTORY)model/3d_model.h \
			$(SOURCE_DIRECTORY)model/settings.cc \
			$(SOURCE_DIRECTORY)model/settings.h

all: build
	$(EXEC) $(COMPILATION_DIRECTORY)$(APP)

build: clean
	@mkdir -p $(COMPILATION_DIRECTORY)
	cp $(SOURCE_DIRECTORY)3DViewer.pro $(COMPILATION_DIRECTORY)$(PROGRAM_NAME).pro
	cd $(COMPILATION_DIRECTORY); qmake $(PROGRAM_NAME).pro
	make -C $(COMPILATION_DIRECTORY)

install: build
	@mkdir -p $(HOME)/Applications/$(PROGRAM_NAME)/
	cp -rf $(COMPILATION_DIRECTORY)$(APP) $(HOME)/Applications/$(PROGRAM_NAME)/

uninstall:
	rm -rf $(HOME)/Applications/$(PROGRAM_NAME)/

dvi:
	$(OPEN) Readme.md

dist:
	cd ..; mkdir $(DIST_DIR); cp -r 3DViewer $(DIST_DIR); tar -czf $(DIST_DIR).tar.gz $(DIST_DIR); \
	rm -rf $(DIST_DIR); cp $(DIST_DIR).tar.gz ./3DViewer/; rm $(DIST_DIR).tar.gz

leaks: tests
	$(LEAK_TEST) ./test

cppcheck:
	cppcheck --enable=all --language=c++ --suppress=unusedFunction --suppress=missingInclude $(SOURCES)

tests: clean
	$(CC) $(SOURCE_DIRECTORY)test/test.cc $(FLAGS) $(WCHECK) -o test
	./test

gcov_report:
	@$(CC) -lgtest --coverage $(SOURCE_DIRECTORY)test/test.cc $(FLAGS) $(WCHECK) -o test
	@./test
	lcov --capture --directory ./ --output-file coverage.info --no-external
	genhtml --output-directory gcov_report coverage.info
	$(OPEN) gcov_report/index.html

clean:
	rm -rf *.o *.out *.a *.gcda *.gcno *.info test valgrind.txt *.h.gch
	rm -rf ./gcov_report/
	rm -rf ./$(COMPILATION_DIRECTORY)*
