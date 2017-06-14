rm httpRequest.o -f
g++ -c httpRequest.cpp -I.
g++ -o main main.c httpRequest.o -I.
./main
# sw=2;ts=2;sts=2;expandtab
