#!/bin/zsh

set -e

function print_usage() {
  echo "Usage:
./run_all.sh [Compile Options]
    Compile Options:
        0: reference code
        1: your code"
}

if [[ $# -ne 1 ]]; then
  print_usage
  exit
else
  if [[ $1 -ne 0 && $1 -ne 1 ]]; then
    print_usage
    exit
  fi
fi

# Build.
set +e
rm -r build &> /dev/null
set -e
mkdir -p build
cd build
if [[ $1 -eq 0 ]]; then
  cmake ..
else
  cmake .. -D CMAKE_CXX_FLAGS="-DCOMPILE_YOUR_CODE"
fi
make
cd ../

# Run.
function run_test() {
  echo "==========================================================================================="
  echo command: $1
  eval $1
}
run_test ./build/01_AssignmentOperator
run_test ./build/03_01_DuplicationInArray
run_test ./build/03_02_DuplicationInArrayNoEdit
run_test ./build/04_FindInPartiallySortedMatrix
run_test ./build/05_ReplaceSpaces
run_test ./build/06_PrintListInReversedOrder
run_test ./build/07_ConstructBinaryTree
run_test ./build/08_NextNodeInBinaryTrees
run_test ./build/09_QueueWithTwoStacks
run_test ./build/10_Fibonacci
