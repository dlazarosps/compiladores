#!/bin/sh

# Para testar, execute: bash run.sh FROM TO
# onde FROM e TO é o sufixo dos arquivos de teste
# exemplo: bash run.sh 1 97

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
tests_folder="../etapa2/testes/"
prefix="asl"

testes_com_erro=""
erros=0

#aplica teste de 1 até @parm files
for i in `seq $files_from $files_to`
do
    printf "* Teste %d:\n" $i

    if (($i < 10)); then
        filename=$prefix"0"$i
    else
        filename=$prefix$i
    fi

    #se existir ERROR no arquivo de teste,
    #considera que o teste espera ERRO como resultado
    if grep -q "ERROR" $tests_folder$filename
    then
        echo "Esperando ERRO"
        should_error=true
    else
        echo "Esperando SUCESSO"
        should_error=false
    fi

    # roda o programa para receber o resultado (erro ou não)
    cat $tests_folder$filename | ./etapa3
    return_value=$?

    if [ $should_error = false ] && [ $return_value != 0 ]; then
        echo "[TEST ERROR] Para o teste "$i", esperava sucesso e recebi erro!"
        ((erros++))
        testes_com_erro=$i","$testes_com_erro
    fi

    if [ $should_error = true ] && [ $return_value -eq 0 ]; then
        echo "[TEST ERROR] Para o teste "$i", esperava erro e recebi sucesso!"
        ((erros++))
        testes_com_erro=$i","$testes_com_erro
    fi

    if [ $should_error = false ] && [ $return_value -eq 0 ]; then
        echo "[TEST OK] Para o teste "$i", esperava sucesso e recebi sucesso!"
    fi

    if [ $should_error = true ] && [ $return_value != 0 ]; then
        echo "[TEST OK] Para o teste "$i", esperava erro e recebi erro!"
    fi

    if [ $return_value -eq 0 ]; then
        # primeiro laço de compilação/descompilação
        ./etapa3 < $tests_folder$filename > eq1.txt
        # segundo laço de compilação/descompilação
        ./etapa3 < eq1.txt > eq2.txt
        # efetiva comparação (arquivos eq1.txt e eq2.txt devem ser idênticos)
        diff eq1.txt eq2.txt
        # verificação do resultado
        return_value=$?

        if [ $return_value != 0 ]; then
            echo "[TEST ERROR] Os arquivos gerados não são iguais!"
            ((erros++))
            testes_com_erro=$i","$testes_com_erro
        fi

        if [ $return_value -eq 0 ]; then
            echo "[TEST OK] Os arquivos gerados são iguais!"
        fi
    fi

    echo
done

if [ $erros -gt 0 ]; then
    echo "Numero total de erros de teste: "$erros
    echo "Erro nos testes:"$testes_com_erro
else
    echo "Nenhum erro encontrado nos testes!"
fi
