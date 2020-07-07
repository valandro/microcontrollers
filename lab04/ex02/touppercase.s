/*
  asmops.s: sum and difference in Assembly.
  
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

	.intel_syntax noprefix

	.text
	
	.global	to_uppercase

#
# void to_uppercase(char* word)
# function to convert a word to uppercase and print them 
#

to_uppercase:
_start:
	push	ebp # save stack position so we can restore it later
	mov	ebp, esp # put stack pointer at base pointer
  mov esi, [ebp + 8] # pointer to the first char of string to auxiliar register (ESI)
  mov edx, 0 # edx it's the string length counter

to_upper:
  mov al, [esi] # esi it's the pointer to the first char
  cmp al, 0x0 # end of string
  je print
  add edx, 1 # increment the string length
  cmp al, 'a' # if char below 'a' then do nothing
  jb next_char
  cmp al, 'z' # if char greater then 'z' then do nothing
  ja next_char
  sub al, 0x20 # Then convert to upper case ASCII value (subtract 0010 0000)
  mov [esi], al # write it back to esi

next_char:
  inc esi # go to next char (*esi++)
  jmp to_upper

print:
  mov ecx, [ebp + 8] # word to be writed
  mov eax, 4 # linux kernel function code for writing function
  mov ebx, 1 # file descriptor, 1 means stdout
  int 0x80 # call write function in the linux kernel
	pop	ebp  # Reset all registers used by the function
	ret
