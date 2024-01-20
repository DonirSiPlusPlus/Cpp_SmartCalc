CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17
LIBS=-lgtest
LEAKS=leaks --atExit -- ./tests

OS=$(shell uname -s)
ifeq ($(OS), Linux)
	LIBS+= -lpthread
	LEAKS=valgrind ./tests
endif

all: test_build install dvi

install:
	@mkdir ../build
	@cp -R ./Model/ ../build/
	@cp -R ./View/ ../build/
	@cp -R controller.h ../build/
	@cd ../build && qmake6 ./cpp_smart.pro
	@cd ../build && make
	@cd ../build && make clean
	@cd ../build && rm -f Makefile
	@cd ../build && rm -f *.stash
	@rm -rf ../build/*.pro ../build/*.cc ../build/*.h ../build/*.cpp ../build/*.ui ../build/*.user

uninstall:
	rm -rf ../build

clean:
	@rm -Rf *.o *.gcno *.gcda *.info report tests valgrind_output .clang-format

dvi:
	cat doc_calc.texi

dist:
	@mkdir smartcalc_cpp
	@cp -R ./Model/ smartcalc_cpp
	@cp -R ./View/ smartcalc_cpp
	@cp -R controller.h smartcalc_cpp
	@cp Makefile *.texi smartcalc_cpp
	@tar -cf smartcalc_cpp.tar smartcalc_cpp
	@gzip smartcalc_cpp.tar
	@rm -rf smartcalc_cpp

tests: test_build
	./tests

leaks: test_build
	$(LEAKS)

clang:
	cp ../materials/linters/.clang-format .
	clang-format -i Model/*.h Model/*.cc View/*.h View/*.cc *.cc *.h
	clang-format -n Model/*.h Model/*.cc View/*.h View/*.cc *.cc *.h

check:
	@echo "Check Model"
	@cppcheck --language=c++ Model/*.h Model/*.cc *.cc 
	@echo "\nCheck View and Controller"
	@cppcheck --language=c++ View/*.h View/*.cc *.h
	@echo "Check MVC done!"

test_build:	s21_calculator.o tests.o
	$(CC) $(CFLAGS) s21_calculator.o tests.o -o tests $(LIBS)

tests.o: tests.cc
	$(CC) $(CFLAGS) -c tests.cc $(LIBS)

s21_calculator.o: Model/s21_calculator.cc
	$(CC) $(CFLAGS) -c Model/s21_calculator.cc
