#!/bin/sh
# This shell script is for checking code style using "uncrustify (v0.59)"

# Set directories
BASE_DIR="$PWD"
SOURCE_DIR=""$BASE_DIR"/../.."

# Set target directory
CHECK_DIRS="$SOURCE_DIR/dart/"

# Set target files
CHECK_FILES=`\
  find "$CHECK_DIRS"\
  -name '*.h'\
  -or -name '*.cpp'
`

# Beautify with uncrustify
cd "$BASE_DIR"
uncrustify -c dart.cfg --no-backup $CHECK_FILES


