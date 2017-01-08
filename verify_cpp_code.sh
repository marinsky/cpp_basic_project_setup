#!/usr/bin/env bash
# This script is a wrapper on code verification which currently includes
# code style analysis only.

# set working directory to script directory
cd "$(dirname "$0")"
# if no arguments passed, then scan the following folders (all sources)
SCAN_PATH=$(echo ./{src/data_providers,src/business_logic,test})
SRC_EXTS='( -name *.h -o -name *.cpp -o -name *.hpp )'
SCAN_FILES="$(find $SCAN_PATH -type f $SRC_EXTS)"

# otherwise scan specific files/folders specified as arguments
if [ ! -z "$1" ]; then
    SCAN_FILES="$*"
fi

# run verification script with extra settings
# google's cpplint requires python2, can be easily ported to python3 if needed
python2.7 3rdparty/styleguide/cpplint/cpplint.py \
    --verbose=0 \
    --counting=toplevel \
    $SCAN_FILES
