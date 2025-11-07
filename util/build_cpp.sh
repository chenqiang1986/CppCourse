input=$1

read -ra arr <<< "$input"

for val in "${arr[@]}"; do
   if [[ $val == *.cpp ]]
   then
       echo "CPP"
   fi
   printf "file: $val\n"
done

