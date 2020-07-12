/*
  countint.c: Count the number of interrupts on Galileo Gen2 IO4.
  
  Copyright (c) 2016, 2020 Walter Fetter Lages <w.fetter@ieee.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    You can also obtain a copy of the GNU General Public License
    at <http://www.gnu.org/licenses>.

*/

#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <unistd.h>

#include <galileo2io.h>

int main(int argc,char * argv[])
{
        unsigned char c;
        struct pollfd pfd;
        int board;
        int number_of_int = 0;
        
        while(1) {

        board=board_name();
        
        if(board == BOARD_GALILEO_GEN1)
            pfd.fd=open("/sys/class/gpio/gpio15/value",O_RDONLY);
        else if(board == BOARD_GALILEO_GEN2)
            pfd.fd=open("/sys/class/gpio/gpio6/value",O_RDONLY);
        else pfd.fd=-1;
        
        if(pfd.fd < 0)
        {
                perror("Opening gpio:");
                return -1;
        }

        read(pfd.fd,&c,1);

        pfd.events=POLLPRI;

        puts("Waiting for interrupt...");

        if(board == BOARD_GALILEO_GEN1)
            pputs("/sys/class/gpio/gpio15/edge","rising");
        else if(board == BOARD_GALILEO_GEN2)
            pputs("/sys/class/gpio/gpio6/edge","rising");

        poll(&pfd,1,-1);
            
        lseek(pfd.fd,0,SEEK_SET);
        read(pfd.fd,&c,1);

        number_of_int++;
        printf("Number of interrupts: %d\n", number_of_int);
            
        if(board == BOARD_GALILEO_GEN1)
            pputs("/sys/class/gpio/gpio15/edge","none");
        else if(board == BOARD_GALILEO_GEN2)
            pputs("/sys/class/gpio/gpio6/edge","none");

        close(pfd.fd);

        }
        return 0;
}