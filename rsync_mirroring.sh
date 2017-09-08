#!/bin/bash
#
# cron + rsyncでの簡易ミラーリング
#

SRC=("/usr/src" "/var" "/tmp" "/home")
DEST=("/mnt/backup_1" "/mnt/backup_2" "/mnt/backup_3" "/mnt/backup_4" "/mnt/backup_5")
RSYNC="/usr/bin/rsync"
RSYNC_OPT="-av --delete --exclude=lost+found --exclude=swap.img"
RSYNC_NICE="ionice -c 2 nice -n 16"
LOGFILE="/var/log/rsync_backup.log"

# check process
PID=$(pgrep -d ', ' -f 'rsync\s(.+)')   &&  \
    echo "$(LANG=C date): ${RSYNC} [${PID}] is already running." >> "${LOGFILE}"    && \
    exit 0

# exec rsync
for ((i = 0; i < ${#SRC[@]}; i++)); do
    for ((j = 0; j < ${#DEST[@]}; j++)); do
        ${RSYNC_NICE} ${RSYNC} ${RSYNC_OPT} "${SRC[$i]}/" "${DEST[$j]}${SRC[$i]}/" 2>> "${LOGFILE}"
        test $? -eq 0   && \
            echo "$(LANG=C date): $RSYNC $RSYNC_OPT ${SRC[$i]}/ ${DEST[$j]}${SRC[$i]}/: done." >> "${LOGFILE}"    || \
            echo "$(LANG=C date): $RSYNC $RSYNC_OPT ${SRC[$i]}/ ${DEST[$j]}${SRC[$i]}/: failure." >> "${LOGFILE}"
    done
done
