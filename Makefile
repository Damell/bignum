all:
	g++ -ggdb -Wall -pedantic -Werror -Wno-long-long -O0 ./main.cpp ./BigNum.cpp ./ShuntingYard.cpp ./Calculator.cpp
compile:
run:
clean:
	echo Cistim to tu...
doc:
count:
	wc -l ./BigNum.h ./BigNum.cpp ./Calculator.h ./Calculator.cpp ./Token.h ./ShuntingYard.h ./ShuntingYard.cpp ./Operator.h


# compile for windows: i686-w64-mingw32-g++ -static-libgcc -static-libstdc++ ./main.cpp ./BigNum.cpp ./ShuntingYard.cpp ./Calculator.cpp
#make all nebo make vytvoří veškeré výstupy, generované ze zdrojového kódu.
#make compile vytvoří binární podobu semestrální práce, výsledek bude uložen do souboru <login>/<login>.
#make run spustí binární podobu semestrální práce.
#make clean smaže všechny vygenerované soubory a uvede adresář <login> do původního stavu.
#make doc vytvoří dokumentaci do adresáře <login>/doc. Dokumentaci musíte vytvořit pomocí programu doxygen, berte to jako výhodu a zkuste dokumentaci uplatnit v předmětu TED. Dokumentaci můžete vygenerovat POUZE v HTML (tedy ne pdf/latex).

