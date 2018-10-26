probs=("complex" "hugeinteger" "rational")


for file in user/*
do
	if [ -d "$file" ]
	then
		echo $file
		cd $file/src/
		for prob in ${probs[*]}
		do
			cp ../../../test/$prob/Test.java $prob/Test.java 2> tmp.txt
			# javac $prob/*.java 2> tmp.txt
			javac $prob/*.java
			java $prob.Test
			# java $prob.Test ../../../test/$prob/input.txt > output.txt 2> tmp.txt
			# diff output.txt ../../../test/$prob/output.txt > /dev/null
			# if [ $? != 0 ]
			# then
			# 	echo $prob "WA"
			# else
			# 	echo $prob "AC"
			# fi
		done
		echo ""
		cd ../../../
	fi
done
