# 06/18/2017 

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.


# Your script should always return a single string.
# Read the above line again.
#
# pinky-bar will always call uzer_func,
# you can write other subroutines/functions
# but they should be called inside uzer_func
#
# Dont worry about the colorization, it's
# handled by pinky-bar.

  .file	"common.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Hello World"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	uzer_func3
	.type	uzer_func3, @function
uzer_func3:
.LFB0:
	.cfi_startproc
	movl	$.LC0, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	uzer_func3, .-uzer_func3
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.ident	"GCC: (Gentoo 5.4.0-r3 p1.3, pie-0.6.5) 5.4.0"
	.section	.note.GNU-stack,"",@progbits
