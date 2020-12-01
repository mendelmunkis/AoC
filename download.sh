#!/bin/sh
YEAR=`date +%Y`
DAY=`date +%-d`
wget "https://adventofcode.com/$YEAR/day/$DAY/input" --header "Cookie: session=$(cat session_cookie)"  -O $YEAR/inputs/input$DAY
cp -f $YEAR/inputs/input$DAY $YEAR/input
