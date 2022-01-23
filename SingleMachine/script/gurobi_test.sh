# /opt/homebrew/bin/bash

input=("80_v1" "100_v1" "120_v1" "140_v1" "160_v1")
for i in "${input[@]}"; do
    echo "running IP with input $i"
    ./bin/TESTrelax_oneparam_c++ < input/${i}.in
done