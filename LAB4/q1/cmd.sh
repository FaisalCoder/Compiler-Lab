#!/bin/sh
flex calc.l
byacc -d calc.y
g++ lex.yy.c -c -o calc.l.o
g++ y.tab.c -c -o calc.y.o
g++ calc.l.o calc.y.o -o calc.o -lfl -m
./calc.o <input >output
