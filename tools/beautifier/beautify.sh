#!/bin/sh
# This shell script is for checking code style using "uncrustify (v0.59)"

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

# Beautify with uncrustify
uncrustify -c "$SCRIPTPATH"/dart.cfg --no-backup $CHECK_FILES


