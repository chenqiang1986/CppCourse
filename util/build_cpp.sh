input=$1

read -ra arr <<< "$input"

for val in "${arr[@]}"; do
   printf "file: $val\n"
done

