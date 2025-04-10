#!/bin/bash

SCORE=0
MAX_SCORE=8
TEST_DIR=tests

make
if [ $? -ne 0 ]; then
  echo "Compile Error"
  echo "Score: 0 / $MAX_SCORE"
  exit 1
fi

for i in {1..4}
do
  cp "$TEST_DIR/input$i.txt" pq.in

  # Run the program with a 3-second timeout
  timeout 3s ./pq
  EXIT_CODE=$?

  if [ $EXIT_CODE -eq 124 ]; then
    echo "Test $i: TIMEOUT (exceeded 3 seconds)"
  elif [ $EXIT_CODE -ne 0 ]; then
    echo "Test $i: RUNTIME ERROR (exit code $EXIT_CODE)"
  else
    diff -wB pq.out "$TEST_DIR/output$i.txt" > result.diff
    if [ $? -eq 0 ]; then
      echo "Test $i: PASS"
      SCORE=$((SCORE+2))
    else
      echo "Test $i: FAIL (wrong output)"
      cat result.diff
    fi
  fi
done

echo "Total Score: $SCORE / $MAX_SCORE"

# Print final result for GitHub Classroom autograding
if [ "$SCORE" -eq "$MAX_SCORE" ]; then
  echo "true"
else
  echo "false"
fi
