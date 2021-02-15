#!/bin/bash -xv

expnum=${1:-1}
HOME=~/

Dir=$HOME/output_temp/exp${expnum}
File=$HOME/output_agg/exp${expnum}.txt

rm $File

$HOME/code/merge $File $Dir run
