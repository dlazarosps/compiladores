#!/bin/sh

# Gambiarra para rodar os testes
echo "Rodando Testes"

# Compila
make all

# Testa existencia de parametros
if [ -z "$1" ]; then
    echo "NO"
    files=12
else
    files=$1
fi

#pasta com os arquivos de teste e prefixo
arquivo="testes/asl"


#aplica teste de 1 até @parm files
for i in `seq 1 $files`
do
    echo $i
    if (($i < 10)); then 
        # echo $arquivo"0"$i
        cat $arquivo"0"$i | ./etapa2
    else
        # echo $arquivo$i
        cat $arquivo$i | ./etapa2
    fi
done