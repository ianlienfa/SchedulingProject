#! /usr/local/bin/bash
directories=("BFS" "BFSCBB" "DFS" "localSearch")
# echo $directoies
for dir in "${directories[@]}"; do
    outfiles=(`ls ../out/$dir`)
    for out in "${outfiles[@]}"; do        
        rm "$dir/$out"
        touch "$dir/$out"
        cat "../out/$dir/$out" | grep min | awk '{if(NF > 3) print $3 $NF}' | awk -F ',' '{print $1 " " $2}' >> "$dir/$out"        
    done
done
