./$1 > $1.out
diff -q $1.out ../$1.out || echo "Test Case 1 Failed"
diff -q ../$1.out $1.out || echo "Test Case 2 Failed"
diff -q $1.out $1.out || echo "Test Case 3 Failed"
