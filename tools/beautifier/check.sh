#!/bin/sh
# This shell script is for checking code style using "uncrustify (v0.59)"

# Set directories

# Absolute path to this script, e.g. /home/user/bin/foo.sh
SCRIPT=$(readlink -f "$0")

# Absolute path this script is in, thus /home/user/bin
SCRIPTPATH=$(dirname "$SCRIPT")

# Absolute path to the project
SOURCE_DIR="$SCRIPTPATH/../.."

# Set target directory
CHECK_DIRS="$SOURCE_DIR/dart/"

# Set target files
CHECK_FILES=`\
  find "$CHECK_DIRS"\
  -name '*.h'\
  -or -name '*.cpp'
`

# Store beautified files with ".uncrustify" suffix
uncrustify -c "$SCRIPTPATH"/dart.cfg -q --suffix .uncrustify $CHECK_FILES

# Check the style by comparing the original files and the beautified files
for entry in $CHECK_FILES
do
  DIFF=`diff -q "$entry" "$entry"".uncrustify"`
  if [ "$DIFF" != "" ]; then
    RESULT=FALSE
    echo "Style error: ""$entry"
  fi
done

# Remove the beautified files
for entry in $CHECK_FILES
do
  rm "$entry"".uncrustify"
done

# Return the result
if [ "$RESULT" = "FALSE" ]; then
  exit 1
else
  exit 0
fi

