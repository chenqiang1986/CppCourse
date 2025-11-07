input=$1

read -ra arr <<< "$input"

for val in "${arr[@]}"; do
   if [[ $val == *.cpp ]]
   then
       base_name=$(basename $val)
       non_ext_base_name=${base_name%.*}
       
       echo " - Run Target: build/$non_ext_base_name"

       i=1
       while :
       do
          if [ $i -eq 3 ]; then
              echo "This is the end of the loop"
              break
          fi
          
          echo "   - Run Test Case $i"
          build/$non_ext_base_name < answers/$non_ext_base_name/$i.in > build/$non_ext_base_name.out
          
          diff -q answers/$non_ext_base_name/$i.out build/$non_ext_base_name.out >/dev/null
          comp_value=$?
          if [ $comp_value -eq 1 ]
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
   fi
done

echo "$total_failure Failures"
exit $total_failure
