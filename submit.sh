#!/bin/sh
YEAR=`date +%Y`
DAY=`date +%-d`
COOKIE=session_cookie
ANS="c"

if [ ${PWD##*/} -gt 2000 ]
then
    if [ ${PWD##*/} -lt 3000 ]
    then
        YEAR=${PWD##*/}
        COOKIE=../session_cookie
    fi
fi

while getopts ":y:d:l:" options; do              # Loop: Get the next option;
                                               # use silent error checking;
                                               # options n and t take arguments.
  case "${options}" in                         # 
    y)                                         # If the option is n,
      YEAR=${OPTARG}                           # set $NAME to specified value.
      ;;                                       # 
    l)                                         # If the option is n,
      LEVEL=${OPTARG}                           # set $NAME to specified value.
      ;;
    d)                                         # If the option is t,
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

read -r ANS

wget --post-data="level=$LEVEL&answer=$ANS" "https://adventofcode.com/$YEAR/day/$DAY/answer" --header "Cookie: session=$(cat $COOKIE)" --output-document=-
