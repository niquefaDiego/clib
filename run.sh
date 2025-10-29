#!/bin/sh

rm -rf build/*

BOLD=$(tput bold)
GREEN=$(tput setaf 2)
CYAN=$(tput setaf 6)
RED=$(tput setaf 1)
RESET=$(tput sgr0)

totalTestCount=0
testPassedCount=0

CompileAndRunTest() {
  totalTestCount=$((totalTestCount+1))
  pathToTest=$1
  echo
  echo "${CYAN}${BOLD} -> Test ${totalTestCount}: ${pathToTest}${RESET}"
  echo "${CYAN}[$pathToTest] Compiling...${RESET}"
  cFilePath="./src/$pathToTest.c"
  hFilePath="./include/$pathToTest.h"
  cTestFilePath="./tests/$pathToTest""_Test.c"
  binaryFilePath="./build/$pathToTest"
  mkdir -p $(dirname $binaryFilePath)  # ensure folder for executable exists
  gcc -std=c2x -I ./include $cTestFilePath $cFilePath -o $binaryFilePath

  if [ $? -ne 0 ]; then
    echo "${RED}[$pathToTest] Compilation failed, see error above.${RESET}\n"
    return 1
  fi

  echo "${CYAN}[$pathToTest] Running test code: ${cTestFilePath}${RESET}"
  valgrind --leak-check=full --quiet --error-exitcode=10 ./$binaryFilePath
  statusCode=$?
  case "$statusCode" in
    "0")
      testPassedCount=$((testPassedCount+1))
      echo "${GREEN}[$pathToTest] Test passed!${RESET}\n"
      ;;
    "10")
      echo "${RED}[$pathToTest] Test failed with status: ${statusCode} (valgrind found a memory leak)${RESET}\n"
      ;;
    "134")
      echo "${RED}[$pathToTest] Test failed with status: ${statusCode} (assertion failed)${RESET}\n"
      ;;
    *)
      echo "${RED}[$pathToTest] Test failed with status: ${statusCode}${RESET}\n"
      ;;
  esac

  return 0
}

CompileAndRunTest "array/Sort"
CompileAndRunTest "ds/DoublyLinkedList"
CompileAndRunTest "ds/ArrayList"

if [ $totalTestCount -eq 0 ]; then
  echo "ERROR: No tests were found"
  return 1
fi

if [ $testPassedCount -eq $totalTestCount ]; then
  echo "${GREEN}${BOLD} -> Passed all $totalTestCount tests${RESET}"
  echo
  return 0
else
  echo "${RED}${BOLD} -> Passed $testPassedCount/$totalTestCount tests${RESET}"
  echo
  return 1
fi