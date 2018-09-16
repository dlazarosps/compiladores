#!/bin/sh

# Para testar, execute: bash run.sh NUMERO_MAX_DE_TESTES

# Gambiarra para rodar os testes
echo "Rodando Testes"

# Compila
make all

# Testa existencia de parametros
if [ -z "$1" ]; then
    files_from=1
else
    files_from=$1
fi

if [ -z "$2" ]; then
    files_to=97
else
    files_to=$2
fi

#pasta com os arquivos de teste e prefixo
tests_folder="testes/"
expect_folder="expect/"
prefix="asl"

#aplica teste de 1 até @parm files
for i in `seq $files_from $files_to`
do
    echo $i

    if (($i < 10)); then
        filename=$prefix"0"$i
    else
        filename=$prefix$i
    fi

    #se existir ERROR no arquivo de teste,
    #considera que o teste espera ERRO como resultado
    if grep -q "ERROR" $tests_folder$filename
    then
        #expected ERROR
        should_error=true
    else
        #expected SUCCESS
        should_error=false
    fi

    cat $tests_folder$filename | ./etapa2
    return_value=$?

    echo $return_value

    if [ $should_error = false ] && [ $return_value != 0 ]; then
        echo "[TEST ERROR] Para o teste "$i", esperava nenhum erro e recebi erro!"
    fi

    if [ $should_error = true ] && [ $return_value -eq 0 ]; then
        echo "[TEST ERROR] Para o teste "$i", esperava erro e recebi nenhum erro!"
    fi
done
