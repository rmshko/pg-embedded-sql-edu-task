ecpg main.pgc
g++ -I /usr/include/postgresql -c main.c
g++ -o main main.o -L /usr/lib/x86_64-linux-gnu -lecpg -lpgtypes
./main
