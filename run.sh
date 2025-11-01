#!/bin/sh

BOLD=$(tput bold)
GREEN=$(tput setaf 2)
CYAN=$(tput setaf 6)
RED=$(tput setaf 1)
RESET=$(tput sgr0)

buildFolder="./build"
sourceFolder="./src"
testsFolder="./tests"
includeFolder="./include"

sharedLibraryFolder="${buildFolder}/library"
mycstdSoPath="${sharedLibraryFolder}/libmycstd.so"

IsCachedBinaryStillValid() {
  folderPath=$1
  existingBinaryPath=$2

  # Check if the folder exists
  if [ ! -d "$folderPath" ]; then
    echo "${RED}${BOLD}Error: Folder '$folderPath' not found.${RESET}"
    exit 1
  fi

  # Check if the reference file exists
  if [ ! -f "$existingBinaryPath" ]; then
    echo "${CYAN}Did not find existing binary '$existingBinaryPath'${RESET}"
    return 0
  fi

  # Find files in the folder that are newer than the reference file
  NEWER_FILES=$(find "$folderPath" -type f -newer "$existingBinaryPath")

  # Check if any newer files were found
  if [ -n "$NEWER_FILES" ]; then
    echo "${CYAN}The following files in '$folderPath' are newer than '$existingBinaryPath':${RESET}"
    echo "${CYAN}$NEWER_FILES${RESET}"
    return 0 # Indicate that newer files were found
  fi

  echo "${CYAN}No files in '$folderPath' are newer than '$existingBinaryPath'${RESET}"
  return 1 # Indicate that no newer files were found
}

CompileMycstdLibrary() {
  echo "${CYAN}Building shared library: $mycstdPath${RESET}"
  export LD_LIBRARY_PATH=$sharedLibraryFolder:$LD_LIBRARY_PATH
  echo "${CYAN}Set environment variable LD_LIBRARY_PATH=${LD_LIBRARY_PATH}${RESET}"

  mkdir -p $(dirname $mycstdSoPath)  # ensure folder for executable exists
  IsCachedBinaryStillValid $sourceFolder $mycstdSoPath
  if [ $? -eq 1 ]; then
    IsCachedBinaryStillValid $includeFolder $mycstdSoPath
    if [ $? -eq 1 ]; then
      echo "${CYAN}No changes detected. Reusing existing binary $mycstdSoPath.${RESET}\n"
      return 0
    fi
  fi
  
  gcc -std=c2x --shared -fPIC -I $includeFolder -o $mycstdSoPath ${sourceFolder}/mycstd.c ${sourceFolder}/**/*.c

  if [ $? -ne 0 ]; then
    echo "${RED}Failed to build shared library, see error above.${RESET}\n"
    exit 1
  else
    echo "${CYAN}Successfully built shared library $mycstdPath${RESET}"
  fi
}

CompileAndRunTest() {
  totalTestCount=$((totalTestCount+1))
  pathToTest=$1
  echo
  echo "${CYAN}${BOLD} -> Test ${totalTestCount}: ${pathToTest}${RESET}"
  hFilePath=".${includeFolder}/$pathToTest.h"
  cTestFilePath="${testsFolder}/${pathToTest}_test.c"
  binaryFilePath="${buildFolder}/tests/$pathToTest"
  mkdir -p $(dirname $binaryFilePath)  # ensure folder for executable exists

  useExistingBinary="false"
  if [ -f $binaryTestFilePath ]; then
    if [ $binaryFilePath -nt $cTestFilePath ]; then
      useExistingBinary="true"
      echo "${CYAN}[$pathToTest] No changes in ${cTestFilePath}, using existing binary ${binaryFilePath}${RESET}"
    fi
  fi

  if [ "$useExistingBinary" = "false" ]; then
    echo "${CYAN}[$pathToTest] Compiling...${RESET}"
    gcc -std=c2x -I $includeFolder $cTestFilePath $cFilePath -o $binaryFilePath  -L${sharedLibraryFolder} -lmycstd
  fi

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

CompileMycstdLibrary

totalTestCount=0
testPassedCount=0

CompileAndRunTest "array/sort"
CompileAndRunTest "ds/dynamic-array"
CompileAndRunTest "ds/doubly-linked-list"
CompileAndRunTest "ds/string"

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