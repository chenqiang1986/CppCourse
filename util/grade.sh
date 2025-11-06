./$1 > $1.out

total_failure=0

diff --brief $1.out ../$1.out >/dev/null
comp_value=$?

if [ $comp_value -eq 1 ]
then
    total_failure = $((total_failure+1))
    echo "Test Case 1 Failed"
else
    echo "Test Case 1 Passed"
fi


diff --brief $1.out $1.out >/dev/null
comp_value=$?

if [ $comp_value -eq 1 ]
then
    total_failure = total_failure+1
    echo "Test Case 2 Failed"
else
    echo "Test Case 2 Passed"
fi

echo "$total_failure Failures"
