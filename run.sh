#!/bin/bash
#===============================================================================
#
#          FILE:  run.sh
#        AUTHOR:  qiurunli 
#       COMPANY:  qihoo
#       CREATED:  2013年07月04日 14时10分38秒 CST
#===============================================================================

g++ extract_syn.cpp -o extract_syn
cp -f /home/qiurunli/synlib .
cat synlib | ./extract_syn > synlib.out
rm synlib

