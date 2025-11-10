input=$1

read -ra arr <<< "$input"

for val in "${arr[@]}"; do
   printf "file: $val\n"
   if [[ $val == *.cpp ]]
   then
       base_name=$(basename $val)
       non_ext_base_name=${base_name%.*}
       
       echo " - Build CPP: build/$non_ext_base_name"
       g++ -g $val -o build/$non_ext_base_name
       compile_exit_code=$?
       if [ $compile_exit_code -ne 0 ]
       then
           exit 1
       fi
   fi
done

echo "list of files under build/"

ls build/

