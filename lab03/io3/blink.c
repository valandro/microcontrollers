/*
  blink.c: Blinks a LED on Galileog gpio3 or Galileo Gen2 IO13.
  
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
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
	char state;
	int led = 0;
	int button = 0;
	char s[20];
	int n;
	

	led=open("/sys/devices/virtual/dmi/id/board_name", O_RDONLY);
	n = read(led, s, sizeof s);
	close(led);
	s[n-1] = '\0'; /* Discards new line */

	if(strncmp(s,"Galileo",sizeof s) == 0)
	    led=open("/sys/class/gpio/gpio3/value", O_WRONLY);
	else if(strncmp(s,"GalileoGen2",sizeof s) == 0) {
	    led=open("/sys/class/gpio/gpio14/value", O_WRONLY);
		button=open("/sys/class/gpio/gpio13/value", O_RDONLY);
	} else return -1;

	for(;;)
	{	
		// Read signal from button
		lseek(button, 0, SEEK_SET);
		read(button, &state, sizeof state);

		// Write state on button
		lseek(led, 0, SEEK_SET);
		write(led, &state, sizeof state);
	}
	
	close(led);
	close(button);

	return 0;
}