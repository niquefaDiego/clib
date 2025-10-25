#!/bin/sh

rm -rf bin/*

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
  hFilePath="./lib/$pathToTest.h"
  cTestFilePath="./test/$pathToTest""_Test.c"
  binaryFilePath="./bin/$pathToTest"
  mkdir -p $(dirname $binaryFilePath)  # ensure folder for executable exists
  gcc -std=c2x -I ./lib $cTestFilePath $cFilePath -o $binaryFilePath

  if [ $? -ne 0 ]; then
    echo "${RED}[$pathToTest] Compilation failed, see error above.${RESET}"
    return 1
  fi

  echo "${CYAN}[$pathToTest] Running test code: ${cTestFilePath}${RESET}"
  $binaryFilePath
  if [ $? -ne 0 ]; then
    echo "${RED}[$pathToTest] Test failed with status: $?${RESET}"
  fi

  echo "${GREEN}[$pathToTest] Test passed!${RESET}"
  echo
  testPassedCount=$((testPassedCount+1))
  return 0
}

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