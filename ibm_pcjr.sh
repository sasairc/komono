#!/bin/bash
#
#    Author:
#        sasairc (@sasairc2)
#
#    License
#        MIT
#

readonly W="\033[48;5;255m  \033[m"
readonly B="\033[48;5;19m  \033[m"
readonly D="\033[48;5;16m  \033[m"

readonly ___BLUE="\033[48;5;19m        \033[m"
readonly __GREEN="\033[48;5;40m        \033[m"
readonly ___CYAN="\033[48;5;6m        \033[m"
readonly ____RED="\033[48;5;160m        \033[m"
readonly __MAGEN="\033[48;5;162m        \033[m"
readonly ___GOLD="\033[48;5;100m        \033[m"
readonly ___GREY="\033[48;5;250m        \033[m"
readonly D__GREY="\033[48;5;243m        \033[m"
readonly B__BLUE="\033[48;5;21m        \033[m"
readonly B_GREEN="\033[48;5;76m        \033[m"
readonly B__CYAN="\033[48;5;14m        \033[m"
readonly B___RED="\033[48;5;1m        \033[m"
readonly B_MAGEN="\033[48;5;165m        \033[m"
readonly B_YELLO="\033[48;5;11m        \033[m"
readonly __WHITE="\033[48;5;255m        \033[m"

function _sleep() {
	if $(which sleepenh > /dev/null 2>&1); then
		SLEEP='sleepenh'
	elif $(which usleep > /dev/null 2>&1); then
		SLEEP='usleep'
	else
   		SLEEP='sleep'
	fi
	${SLEEP} ${1} > /dev/null
}

function _margin_width() {
	local cols=$(tput cols)
	local width=$(expr \( ${cols} - ${1} \) / 2)
	MARGIN_W=$(
			for i in `seq 1 ${width}`; do
				echo -n " "
			done
		)
}

function _margin_height() {
	local lines=$(tput lines)
	local height=$(expr \( ${lines} - ${1} \) / 2)
	MARGIN_H=$(
			for i in `seq 1 ${height}`; do
				echo " "
			done
		)
}

function _initscr() {
	clear
	trap 'tput cnorm; exit 1' SIGINT
	trap 'tput cnorm; exit 0' EXIT
	tput civis
}

function _endscr() {
	clear
	tput cnorm
}

function ibm_pc_jr() {
_margin_width 170
_margin_height 50
local PCJR="
${MARGIN_H}
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$B$B$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$W$W$W$W$W$W$W$B$B$B$B$B$B$B$B$B$B$W$W$W$W$W$W$W$B$B$B$B$B$B$W$W$W$W$W$W$W$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$W$W$W$W$W$W$W$B$B$B$B$B$B$B$B$B$B$W$W$W$W$W$W$W$B$B$B$B$B$B$W$W$W$W$W$W$W$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$W$W$W$W$W$W$W$B$B$B$B$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$W$W$W$W$W$W$W$B$B$B$B$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$W$W$W$W$W$W$W$B$B$B$B$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$W$W$W$W$W$W$W$B$B$B$B$B$B$B$B$B$B$W$W$W$W$W$W$W$B$B$B$B$B$B$W$W$W$W$W$W$W$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$W$W$W$W$W$W$W$B$B$B$B$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$W$W$W$W$W$W$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$W$W$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$B$B$B$B$B$B$B$B$B$B$B$B$B$B$W$W$W$W$W$W$W$W$W$W$W$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B$B
${MARGIN_W}$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$___BLUE$__GREEN$___CYAN$____RED$__MAGEN$___GOLD$___GREY$D__GREY$B__BLUE$B_GREEN$B__CYAN$B___RED$B_MAGEN$B_YELLO$__WHITE$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$___BLUE$__GREEN$___CYAN$____RED$__MAGEN$___GOLD$___GREY$D__GREY$B__BLUE$B_GREEN$B__CYAN$B___RED$B_MAGEN$B_YELLO$__WHITE$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$___BLUE$__GREEN$___CYAN$____RED$__MAGEN$___GOLD$___GREY$D__GREY$B__BLUE$B_GREEN$B__CYAN$B___RED$B_MAGEN$B_YELLO$__WHITE$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$___BLUE$__GREEN$___CYAN$____RED$__MAGEN$___GOLD$___GREY$D__GREY$B__BLUE$B_GREEN$B__CYAN$B___RED$B_MAGEN$B_YELLO$__WHITE$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$___BLUE$__GREEN$___CYAN$____RED$__MAGEN$___GOLD$___GREY$D__GREY$B__BLUE$B_GREEN$B__CYAN$B___RED$B_MAGEN$B_YELLO$__WHITE$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$___BLUE$__GREEN$___CYAN$____RED$__MAGEN$___GOLD$___GREY$D__GREY$B__BLUE$B_GREEN$B__CYAN$B___RED$B_MAGEN$B_YELLO$__WHITE$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$___BLUE$__GREEN$___CYAN$____RED$__MAGEN$___GOLD$___GREY$D__GREY$B__BLUE$B_GREEN$B__CYAN$B___RED$B_MAGEN$B_YELLO$__WHITE$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$___BLUE$__GREEN$___CYAN$____RED$__MAGEN$___GOLD$___GREY$D__GREY$B__BLUE$B_GREEN$B__CYAN$B___RED$B_MAGEN$B_YELLO$__WHITE$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$___BLUE$__GREEN$___CYAN$____RED$__MAGEN$___GOLD$___GREY$D__GREY$B__BLUE$B_GREEN$B__CYAN$B___RED$B_MAGEN$B_YELLO$__WHITE$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$___BLUE$__GREEN$___CYAN$____RED$__MAGEN$___GOLD$___GREY$D__GREY$B__BLUE$B_GREEN$B__CYAN$B___RED$B_MAGEN$B_YELLO$__WHITE$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
${MARGIN_W}$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D$D
"
echo -e "${PCJR}"
}

# main
_initscr

ibm_pc_jr
read

_endscr
