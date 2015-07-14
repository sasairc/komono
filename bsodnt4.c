/*
 * bsodnt4.c
 * 
 * gcc bsodnt4.c -lncurses -o bsodnt4
 */

#include <unistd.h>
#include <ncurses.h>

int init_ntkrnl(WINDOW* win, int y);
int do_bsod(WINDOW* win, int y);

int main(int argc, char* argv[])
{
    int     y   = 0;
    WINDOW* win = NULL;

    initscr();
    noecho();
    curs_set(0);
    start_color();
    assume_default_colors(COLOR_WHITE, COLOR_BLUE);

    win = newwin(LINES, COLS - 1, 0, 0);
    y = init_ntkrnl(win, y);
    y += 2;
    y = do_bsod(win, y);
    while (!wgetch(win));

    wclear(win);
    wrefresh(win);
    endwin();

    return 0;
}

int init_ntkrnl(WINDOW* win, int y)
{
    int     i   = 0,
            j   = 0,
            k   = 0;
    char*   m[] = {
        "Microsoft (R) Windows NT (TM) Version 4.0 (build 1381: Service Pack 6)\n",
        "2 System Processor [256 MB Memory] MultiProcessor Kernel\n",
        NULL,
    };

    for (i = 0; m[i] != NULL; i++, y++) {
        mvwaddstr(win, y, 0, m[i]);
        wrefresh(win);
    }
    for (j = 0; j < 48; j++) {
        if (j / 24) {
            mvwaddstr(win, y, k, ".");
            k++;
        }
        mvwaddstr(win, (y + 1), 0, "_");
        wrefresh(win);
        usleep(100000);
        mvwaddstr(win, (y + 1), 0, " ");
        wrefresh(win);
        usleep(100000);
    }

    return y;
}

int do_bsod(WINDOW* win, int y)
{
    int     i   = 0;
    char*   m[] = {
        "*** STOP: 0x0000000A (0x00000000,0x0000001a,0x00000000,0x00000000)\n",
        "KMODE_EXCEPTION_NOT_HANDLED*** Address 8038c510 has base at 8038c000 - Ntfs.sys\n",
        "\n",
        "CPUID:GenuineIntel f.1.8          SYSVER 0xf0000565\n",
        "\n",
        "Dll Base DateStmp - Name               Dll Base DateStmp - Name\n",
        "80100000 2e53fe55 - ntoskrnl.exe       80400000 2e53eba6 - hal.dll\n",
        "80010000 2e41884b - Aha154x.sys        80013000 2e4bc29a - SCSIPORT.SYS\n",
        "8001b000 2e4e7b6b - Scsidisk.sys       80220000 2e53f238 - Ntfs.sys\n",
        "fe420000 2e406607 - Floppy.SYS         fe430000 2e406618 - Scsicdrm.SYS\n",
        "fe440000 2e406659 - Fs_Rec.SYS         fe450000 2e40660f - Null.SYS\n",
        "fe460000 2e4065f4 - Beep.SYS           fe470000 2e406634 - Sermouse.SYS\n",
        "fe480000 2e42a4a4 - i8042prt.SYS       fe490000 2e40660d - Mouclass.SYS\n",
        "fe4a0000 2e40660c - Kbdclass.SYS       fe4c0000 2e4065e2 - VIDEOPRT.SYS\n",
        "fe4b0000 2e53d49d - ati.SYS            fe4d0000 2e4065e8 - vga.sys\n",
        "fe4e0000 2e406655 - Msfs.SYS           fe4f0000 2e414f30 - Npfs.SYS\n",
        "fe510000 2e53f222 - NDIS.SYS           fe500000 2e40719b - lance.sys\n",
        "fe550000 2e406697 - TDI.SYS            fe530000 2e47c740 - nbf.sys\n",
        "fe560000 2e5279d9 - nwlnkipx.sys       fe570000 2e53a89e - nwlnknb.sys\n",
        "fe580000 2e494973 - tcpip.sys          fe5a0000 2e5256b8 - afd.sys\n",
        "fe5b0000 2e5279d3 - netbt.sys          fe5d0000 2e4167f7 - netbios.sys\n",
        "fe5e0000 2e4066b3 - mup.sys            fe5f0000 2e4f9f51 - rdr.sys\n",
        "fe630000 2e53f24a - srv.sys            fe660000 2e516062 - nwlnkspx.sys",
        "\n",
        "Address  dword dump   Build [1381]                             - Name\n",
        "ff541e4c fe5105df fe5105df 00000001 ff640128 fe4a8228 000002fe - NDIS.SYS\n",
        "ff541e60 fe501368 fe501368 00000246 00004002 00000000 00000000 - lance.sys\n",
        "ff541eb4 fe481509 fe481509 ff6688c8 ff668288 00000000 ff668138 - i8042prt.SYS\n",
        "ff541ee0 fe481ea8 fe481ea8 fe482078 00000000 ff541f04 8013c58a - i8042prt.SYS\n",
        "ff541ee4 fe482078 fe482078 00000000 ff541f04 8013c58a ff6688c8 - i8042prt.sys\n",
        "ff541ef0 8013c58a 8013c58a ff6688c8 ff668040 80405900 00000031 - ntoskrnl.exe\n",
        "ff541efc 80405900 80405900 00000031 06060606 06060606 06060606 - hal.dll\n",
        "\n",
        "Restart and set the recovery options in the system control panel\n",
        "or the /CRASHDEBUG system start option. If this message reappears,\n",
        "contact your system administrator or technical support group.\n",
        NULL,
    };

    for (i = 0; m[i] != NULL; i++, y++) {
        mvwaddstr(win, y, 0, m[i]);
        wrefresh(win);
        usleep(5000);
    }

    return y;
}