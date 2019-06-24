#/bin/bash
i=1
while [ $i -le 1024 ]
do
    ./desempenhoTLB $i 10000 >> tempoMedio
    i=$(( $i*2 ))
done