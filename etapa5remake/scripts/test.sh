#!/bin/sh

# Para testar, execute: bash test.sh BINARY_LOCATION SOURCE_FOLDER OUTPUT_FOLDER
# Exemplo: bash test.sh ../etapa5 test_programs output

# Testa existencia de parametros
if [ -z "$1" ]; then
    exit 1
else
    binary_location=$1
fi

if [ -z "$2" ]; then
    exit 1
else
    source_folder=$2
fi

if [ -z "$3" ]; then
    exit 1
else
    output_folder=$3
fi

for file in $source_folder/*; do
    filename=${file##*/}
    mkdir -p $output_folder
    $binary_location < $source_folder/$filename > $output_folder/$filename
    python ./ilocsim.py -x -t -s --data 500 --stack 1000 $output_folder/$filename > $output_folder/"r_$filename" 
done
