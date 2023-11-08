FILE_NAME_S=Maze
FILE_NAME_L=Maze-1.0

.PHONY: all
all: install start

.PHONY: install
install:
	cmake -S . -B ./build && cd ./build && make

start:
	./build/$(FILE_NAME_S)

.PHONY: uninstall
uninstall:
	rm -rf build

.PHONY: open
open:
	cd build && ./$(FILE_NAME_S)

.PHONY: clean
clean:
	rm -rf build
	rm -rf $(FILE_NAME_L)
	rm -f $(FILE_NAME_L).tar.gz
	rm -f *.info *.gcda *.gcno *.gcov *.css *.html
	rm -rf coverage
	rm -rf doxygen/html doxygen/latex

.PHONY: dvi
dvi:
	cd doxygen && doxygen Doxyfile && open html/index.html

.PHONY: dist
dist:
	tar czvf $(FILE_NAME_L).tar.gz ./Model ./View ./Controller ./doxygen/Doxyfile \
	CMakeLists.txt main.cc Makefile
