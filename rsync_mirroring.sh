#!/bin/bash
#
# cron + rsyncでの簡易ミラーリング
#

SRC=("/usr/src" "/var" "/tmp" "/home")
DEST=("/mnt/backup_1" "/mnt/backup_2" "/mnt/backup_3")
RSYNC="/usr/bin/rsync"
RSYNC_OPT="-av --delete --exclude lost+found"
LOGFILE="/var/log/rsync_backup.log"

# remove /var/cache/apt/archives
#apt-get clean

for ((i = 0; i < ${#SRC[@]}; i++)); do
    for ((j = 0; j < ${#DEST[@]}; j++)); do
        $RSYNC $RSYNC_OPT "${SRC[$i]}/" "${DEST[$j]}${SRC[$i]}/" 2>> "$LOGFILE"
        test $? -eq 0   && \
            echo "$(LANG=C date): $RSYNC $RSYNC_OPT ${SRC[$i]}/ ${DEST[$j]}${SRC[$i]}/: done." >> "$LOGFILE"    ||  \
            echo "$(LANG=C date): $RSYNC $RSYNC_OPT ${SRC[$i]}/ ${DEST[$j]}${SRC[$i]}/: failure." >> "$LOGFILE"
    done
done
