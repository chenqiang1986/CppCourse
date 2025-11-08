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
       timeout 10s build/$non_ext_base_name < answers/$non_ext_base_name/$i.in > build/$non_ext_base_name.out
       execute_exit_code=$?
       echo "   - Exit code $execute_exit_code"
       
       diff -q answers/$non_ext_base_name/$i.out build/$non_ext_base_name.out >/dev/null
       diff_exit_code=$?
       if [ $execute_exit_code -eq 124 ]
       then
           total_failure=$((total_failure+1))
           total_timeout=$((total_timeout+1))
           echo "  - Test Case $i Timeout."
       elif [ $execute_exit_code -ne 0 ]
       then
           total_failure=$((total_failure+1))
           total_execution_error=$((total_execution_error+1))
           echo "  - Test Case $i Finish with Execution Error."
       elif [ $diff_exit_code -eq 1 ]
       then
           total_failure=$((total_failure+1))
           total_diff=$((total_diff+1))
           echo "   - Test Case $i Finish with Wrong Answer, See Diff Below"
           diff answers/$non_ext_base_name/$i.out build/$non_ext_base_name.out
       else
           total_pass=$((total_pass+1))
           echo "   - Test Case $i Passed"
       fi
       echo " "
       ((i++))
    done

    if [ $i -eq 1 ]
    then
       echo "No Test Case Data for $non_ext_base_name, Double Check Your Filename."
       exit 1
    fi
}

total_failure=0
total_timeout=0
total_execution_error=0
total_diff=0
total_pass=0

for val in "${arr[@]}"; do
   if [[ $val == *.cpp ]]
   then
       base_name=$(basename $val)
       non_ext_base_name=${base_name%.*}
       
       echo " - Run Target: build/$non_ext_base_name"
       run_cpp_target
   fi
done

echo "Passed Case: $total_pass"
echo "Failed Cases: $total_failure"
echo " - Timeout Case: $total_timeout"
echo " - Execution Error: $total_execution_error"
echo " - Wrong Answer: $total_diff"
echo "Pass Rate: $((total_pass/(total_failure+total_pass)))"
exit $total_failure
