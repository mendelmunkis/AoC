#!/bin/sh
YEAR=`date +%Y`
DAY=`date +%-d`
COOKIE=session_cookie
OUTPUT=$YEAR/inputs

if [ ${PWD##*/} -gt 2000 ]
then
    if [ ${PWD##*/} -lt 3000 ]
    then
        YEAR=${PWD##*/}
        COOKIE=../session_cookie
        OUTPUT=inputs
    fi
fi

while getopts ":y:d:f:" options; do
 case "${options}" in
    y)
      YEAR=${OPTARG}                           # set $NAME to specified value.
      ;;
    d)
      DAY=${OPTARG}                          # Set $TIMES to specified value.
      ;;
    f)
      FILE=${OPTARG}                          # Set $TIMES to specified value.
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


wget "https://adventofcode.com/$YEAR/day/$DAY/input" --header "Cookie: session=$(cat $COOKIE)"  -O $OUTPUT/input$DAY
cp -f $OUTPUT/input$DAY $OUTPUT/../input
if [[ -n $FILE ]]
then
    echo $FILE
    FILE="$FILE.c"
    echo $FILE
    cp template.c $YEAR/$FILE
    cd $YEAR
    nano $FILE
fi
