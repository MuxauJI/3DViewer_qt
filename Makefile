FLAGS=-Wall -Wextra -Werror -std=c11 #-fsanitize=address -pedantic
LIBS=-lcheck
OS:=$(shell uname -s)
BIN_FILE=3DViewer_v1-0
ifeq ($(OS), Darwin)
	FLAGS += -D MACOS
else
	LIBS += -lsubunit -lrt -lm -lpthread
endif

rebuild: clean all

all: test gcov_report dvi install

install:
	qmake6 ./qt/3DViewer_test.pro -o ./qt/$(BIN_FILE)_makefile
	cd ./qt && make -f $(BIN_FILE)_makefile
	rm -rf ./qt/moc_* ./qt/*.o ./qt/$(BIN_FILE)_makefile ./qt/.qmake.stash
ifeq ($(OS), Darwin)
	open ./build/$(BIN_FILE).app/
else
	./build/$(BIN_FILE)
endif

uninstall:
ifeq ($(OS), Darwin)
	rm -rf ./build/$(BIN_FILE).app ./build/$(BIN_FILE).tar.gz
else
	rm -rf ./build/$(BIN_FILE) ./build/$(BIN_FILE).tar.gz
endif

dvi:
	doxygen Doxyfile
	@sh -c "if grep -iq microsoft /proc/version ; then cd ./html; cmd.exe /c start index.html; else open ./html/index.html; fi"

dist: uninstall install
ifeq ($(OS), Darwin)
	cd ./build && tar -czvf $(BIN_FILE).tar.gz $(BIN_FILE).app
else
	cd ./build && tar -czvf $(BIN_FILE).tar.gz $(BIN_FILE)
endif

localtest: clean ./tests/localtest.c ./core/parser.o
	@gcc $(FLAGS) -c ./tests/localtest.c -o ./tests/localtest.o
	@gcc $(FLAGS) ./tests/localtest.o ./core/parser.o $(LIBS) -o ./tests/test
	@./tests/test

parser.o: core/parser.c
	@gcc $(FLAGS) -c ./core/parser.c -o ./core/parser.o

test: clean ./core/parser.o
	gcc $(FLAGS) -c ./tests/test_parser.c -o ./tests/test_parser.o
	gcc $(FLAGS) ./tests/test_parser.o ./core/parser.o $(LIBS) -o ./tests/test
	./tests/test

gcov_report:
	gcc $(FLAGS) -c ./core/parser.c --coverage -o ./core/parser.o
	gcc $(FLAGS) -c ./tests/test_parser.c -o ./tests/test_parser.o
	gcc $(FLAGS) ./tests/test_parser.o ./core/parser.o --coverage $(LIBS) -o ./tests/test
	./tests/test
	lcov -t "3DViewer" -o parser.info -c -d .
	genhtml -o report parser.info
	rm -rf ./core/*.o ./core/*.gcda ./core/*.gcno *.info ./tests/test ./tests/*.o
	@sh -c "if grep -iq microsoft /proc/version ; then cd ./report/core; cmd.exe /c start index.html; else open ./report/core/index.html; fi"

clean: uninstall
	@rm -rf ./html ./latex ./report ./core/*.o ./core/*.gcda ./core/*.gcno *.info ./tests/test ./tests/*.o CPPLINT.cfg cpplint.py
	@rm -rf ./qt/*.o ./qt/moc_* ./qt/.qmake.stash ./qt/Makefile ./qt/3DViewer_test.pro.*

clf:
	clang-format -n --style=Google ./core/*.[ch] ./tests/*.[ch]

cpk:
	cppcheck ./core/*.[ch] ./tests/*.[ch]

cpl:
	cp ./linters/CPPLINT.cfg ./linters/cpplint.py ./
	python3 cpplint.py --extensions=c ./core/*.[ch] ./tests/*.[ch]
	rm -rf CPPLINT.cfg cpplint.py

style: clf cpk cpl

leaks: parser.o
	gcc $(FLAGS) -c ./tests/test_parser.c -o ./tests/test_parser.o
	gcc $(FLAGS) ./tests/test_parser.o ./core/parser.o $(LIBS) -o ./tests/test
ifeq ($(OS), Darwin)
	leaks -atExit -- ./test
else
	valgrind --leak-check=full ./test
endif
