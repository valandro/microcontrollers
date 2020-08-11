/*
  spitx.c: Transmits a string in the SPI bus using the hardware controller.
  
  Copyright (c) 2016 Walter Fetter Lages <w.fetter@ieee.org>

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
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

int main(int argc,char *argv[])
{
	int fd;
	uint8_t mode=SPI_MODE_0;
	uint8_t lsb=0;
	uint8_t bpw=8;
	uint32_t rate=20000;
	int n;
	
	if(argc != 3)
	{
		printf("Usage: spitx device string\n");
		return -1;
	}
	
	if((fd=open(argv[1],O_RDWR))==-1)
	{
		perror("Can't open device");
		return -1;
	}
	if(ioctl(fd,SPI_IOC_WR_MODE,&mode))
	{
		perror("Can't write clock mode");
		return -1;
	}
	if(ioctl(fd,SPI_IOC_WR_LSB_FIRST,&lsb))
	{
		perror("Can't read LSB mode");
		return -1;
	}
	if(ioctl(fd,SPI_IOC_WR_BITS_PER_WORD,&bpw))
	{
		perror("Can't read bits per word");
		return -1;
	}
	if(ioctl(fd,SPI_IOC_WR_MAX_SPEED_HZ,&rate))
	{
		perror("Can't read maximal rate");
		return -1;
	}
	if((n=write(fd,argv[2],strlen(argv[2]))) > 0)
	{
		printf("Transmited %d bytes.\n",n);
	}
	else
	{
		perror("Can't transmit data");
		return -1;
	}	
	sleep(3);
	close(fd);
	return 0;
}