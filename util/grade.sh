input=$1

read -ra arr <<< "$input"

run_cpp_target() {
    i=1
    while :
    do
       if [ ! -f answers/$non_ext_base_name/$i.in ]; then
           echo "This is the end of the loop"
           break
       fi
       
       echo "   - Run Test Case $i"
       build/$non_ext_base_name < answers/$non_ext_base_name/$i.in > build/$non_ext_base_name.out
       execute_exit_code=$?
       echo "   - Exit code $execute_exit_code"
       
       diff -q answers/$non_ext_base_name/$i.out build/$non_ext_base_name.out >/dev/null
       diff_exit_code=$?
       if [ $execute_exit_code -ne 0 ]
       then
          total_failure=$((total_failure+1))
          echo "  - Test Case $i Finish with Error."
       elif [ $diff_exit_code -eq 1 ]
       then
           total_failure=$((total_failure+1))
           echo "   - Test Case $i Failed, See Diff Below"
           diff answers/$non_ext_base_name/$i.out build/$non_ext_base_name.out
       else
           echo "   - Test Case $i Passed"
       fi
       echo " "
       ((i++))
    done
}

for val in "${arr[@]}"; do
   if [[ $val == *.cpp ]]
   then
       base_name=$(basename $val)
       non_ext_base_name=${base_name%.*}
       
       echo " - Run Target: build/$non_ext_base_name"
       run_cpp_target
   fi
done

echo "$total_failure Failures"
exit $total_failure
