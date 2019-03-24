#!/bin/bash
gcc -std=c99 -Wall -pedantic checkVerbForms2.c ../libmorph.c ../GreekForms.c ../accent.c ../utilities.c ../augment.c ../ending.c ../specialverbs.c -I.. -o checkVerbForms2
./checkVerbForms2
diff -u paradigm_with_tonos.txt new.txt
#diff -u paradigm.txt new.txt
if [ $? == "0" ]
then
echo "No Changes"
else
echo "Has Changes"
fi
