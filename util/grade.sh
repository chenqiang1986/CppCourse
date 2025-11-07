input=$1

read -ra arr <<< "$input"

for val in "${arr[@]}"; do
   printf "file: $val\n"
   if [[ $val == *.cpp ]]
   then
       base_name=$(basename $val)
       non_ext_base_name=${base_name%.*}
       
       echo " - Run Target: build/$non_ext_base_name"
       echo "   - Run Test Case 1"
       build/$non_ext_base_name < answers/$non_ext_base_name/1.in > build/$non_ext_base_name.out

       diff answers/$non_ext_base_name/1.out build/$non_ext_base_name.out >/dev/null
       comp_value=$?
       if [ $comp_value -eq 1 ]
       then
           total_failure=$((total_failure+1))
           echo "   - Test Case 1 Failed"
       else
           echo "   - Test Case 1 Passed"
       fi
   fi
done

echo "$total_failure Failures"
exit $total_failure
