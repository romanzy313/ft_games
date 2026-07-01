#!/bin/bash

gcc *.c *.h -g3 -fsanitize=address -o game.out

./game.out $@

rm ./game.out
