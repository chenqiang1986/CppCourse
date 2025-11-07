input=$1

read -ra arr <<< "$input"

for val in "${arr[@]}"; do
   printf "file: $val\n"
   if [[ $val == *.cpp ]]
   then
       base_name=$(basename $val)
       echo "CPP: $base_name"
   fi
done

