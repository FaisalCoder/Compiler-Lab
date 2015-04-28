#!/bin/sh
flex bcalc.l
byacc -d bcalc.y
g++ lex.yy.c -c -o bcalc.l.o
g++ y.tab.c -c -o bcalc.y.o
g++ bcalc.l.o bcalc.y.o -o bcalc.o -lfl -m
./bcalc.o <input >output
