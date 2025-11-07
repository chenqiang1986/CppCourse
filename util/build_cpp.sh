input=$1

read -ra arr <<< "$input"

for val in "${arr[@]}"; do
   printf "file: $val\n"
   if [[ $val == *.cpp ]]
   then
       base_name=$(basename $val)
       non_ext_base_name=${base_name%.*}
       echo "CPP: $non_ext_base_name"
   fi
done

