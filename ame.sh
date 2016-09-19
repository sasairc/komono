#!/bin/bash

F="[3m　[23m"
C="clangsay -f vim --think"

function ame() {
echo -ne "\
                                                \n\
                                                \n\
                                                \n\
                                                \n\
                                                \n\
                                                \n\
                                                \n\
                                                \n\
                $F$F$F$F$F$F$F$F                \n\
                　　　 $F　　　                 \n\
                $F$F$F$F$F$F$F$F                \n\
                $F　　 $F　　 $F                \n\
                $F $F　$F $F　$F                \n\
                $F　$F $F　$F $F                \n\
                $F $F　$F $F　$F                \n\
                $F　$F $F　$F $F                \n\
                　　　　　　　　                \n\
                　あ　　　　め　                \n\
" | sed -e "$1"
}

while true; do clear; ame "1~2s/  /,\'/g" | $C; sleep 1; clear; ame "2~3s/  /\',/g" | $C; sleep 1; clear; done
