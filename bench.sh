#!/bin/sh
DAY=0
#FILES=$( cat README)
#for FILE in $FILES
FIRSTSUM=0
SECONDSUM=0
echo -e "Day\tPart 1\t\tPart 2\t\tTotal"
while read FILES
do
    ((DAY=DAY+1))
    if [ $DAY -eq 26 ]
    then
        break
    fi
    FILE=$( echo -e "$FILES" | sed 's/ \{3,\}/\t/')
    FILE=$( echo -e "$FILE" | cut -sf2-)
    FILE=$( echo -e "$FILE" | tr -s \ )
    FLAGS=$( echo -e "$FILE" | cut -d\   -sf3-)
    FILE=$( echo -e "$FILE" | cut -d\  -f1)
    sed  -e '1 i #include "../bench.h"' -e '/int main (int argc, char \* argv\[])/{
    N;a \START
    }' -e '/\\n",result);/a \END
    ' $FILE | tee exam | gcc -O3 -x c - $FLAGS
    FIRST=0
    for ((i = 0 ; i < 9 ; i++))
    do
        OUT=$( ./a.out 1 inputs/input$DAY | cut -d\  -sf1)
        if [ $i -ge 4 ]
        then
            FIRST=$( echo -e "scale=10; $FIRST+$OUT\n" | bc)
        fi
    done
    FIRST=$( echo -e "scale=10; $FIRST/5\n" | bc)
    SECOND=0
    if [ $DAY -le 24 ]
    then
        for ((i = 0 ; i < 9 ; i++))
        do
            OUT=$( ./a.out 2 inputs/input$DAY | cut -d\  -sf1)
            if [ $i -ge 4 ]
            then
                SECOND=$( echo -e "scale=10; $SECOND+$OUT\n" | bc)
            fi
        done
        SECOND=$( echo -e "scale=10; $SECOND/5\n" | bc)
    fi
    TOTAL=$( echo -e "scale=10; $FIRST+$SECOND\n" | bc)
    echo -e "$DAY\t$FIRST\t$SECOND\t$TOTAL"
    FIRSTSUM=$( echo -e "scale=10; $FIRST+$FIRSTSUM\n" | bc)
    SECONDSUM=$( echo -e "scale=10; $SECOND+$SECONDSUM\n" | bc)
done < README
    TOTAL=$( echo -e "scale=10; $FIRSTSUM+$SECONDSUM\n" | bc)
    echo -e "Totals\t$FIRSTSUM\t$SECONDSUM\t$TOTAL"
