#!/bin/sh
flex regex.l
byacc -d regex.y
g++ lex.yy.c -c -o regex.l.o
g++ y.tab.c -c -o regex.y.o
g++ regex.l.o regex.y.o -o regex.o -lfl -m
./regex.o <input >output
