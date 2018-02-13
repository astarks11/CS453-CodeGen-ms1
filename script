#~/bin/bash
TESTCASE=/home/cs453/spring18/TestCases/assg2ms1/test*.c
TESTOUT=/home/cs453/spring18/TestCases/assg2ms1/out*
TESTDIR=/home/cs453/spring18/TestCases/assg2ms1/

# Compiles program
: $(make compile)

printf "Generating the MIPS assembly...\n"

for f in $TESTCASE
do
  echo "Testcase: $(basename "$f")"
  compile < $f > $(basename "$f" .c).s
  wait
done

printf "\nNow producing the diff...\n"

# Calculates number of test cases
TOTALTESTS=$(find $TESTDIR -type f -name 'out*' | wc -l)
i=0

# Runs the generated assembly files in SPIM and does a diff against official test cases
for f in $TESTOUT
do
  # Grabs the number from the end of file and appends it to the filename
  NAME=$(basename "$f")
  NUM=${NAME//[!0-9]/}.s
  FILE="test$NUM"

  echo "Testcase: $FILE"

  spim -f $FILE > $(basename "$f")
  wait

  DIFF=$(diff <(tail -n +6 $(basename "$f")) $f)
 
  if [ "$DIFF" != "" ]; then
    echo "$DIFF"
    printf "FAILED"
  else
    printf "PASSED"
    let "i++"
  fi

  printf "\n\n"
  wait
done

printf "RESULT: \n"$i"/"$TOTALTESTS" PASSED\n"

# Removes all intermediate files from compiling
# NOTE: Deletes files that start with "test" and "out"
: $(make clean)
: $(rm test* out*)