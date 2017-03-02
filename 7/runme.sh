#!/bin/sh
echo "Stückzahl der Streifen: 10000000"
echo "make"
make
echo "sequentiell:"
time ./calc_pi_sequential 10000000
echo "kritisch:"
time ./calc_pi_critical 10000000
echo "atomic:"
time ./calc_pi_atomic 10000000
echo "reduction:"
time ./calc_pi_reduction 10000000
echo "Fertig, beginne mit clean"
make clean
echo "terminate"