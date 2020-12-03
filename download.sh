#!/bin/sh
YEAR=`date +%Y`
DAY=`date +%-d`
while getopts ":y:d:" options; do
 case "${options}" in
    y)
      YEAR=${OPTARG}                           # set $NAME to specified value.
      ;;
    d
      DAY=${OPTARG}                          # Set $TIMES to specified value.
      ;;
    :)                                         # If expected argument omitted:
      echo "Error: -${OPTARG} requires an argument."
      exit_abnormal                            # Exit abnormally.
      ;;
    *)                                         # If unknown (any other) option:
      exit_abnormal                            # Exit abnormally.
      ;;
  esac
done


wget "https://adventofcode.com/$YEAR/day/$DAY/input" --header "Cookie: session=$(cat session_cookie)"  -O $YEAR/inputs/input$DAY
cp -f $YEAR/inputs/input$DAY $YEAR/input
