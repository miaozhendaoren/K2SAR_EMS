#  Copyright (C) 1998-2006 HighTec EDV-Systeme GmbH.
# 
# This file is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2, or (at your option) any
# later version.
# 
# In addition to the permissions in the GNU General Public License, the
# Free Software Foundation gives you unlimited permission to link the
# compiled version of this file with other programs, and to distribute
# those programs without any restriction coming from the use of this
# file.  (The General Public License restrictions do apply in other
# respects; for example, they cover modification of the file, and
# distribution when not linked into another program.)
# 
# This file is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING.  If not, write to
# the Free Software Foundation, 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
# 
#    As a special exception, if you link this library with files
#    compiled with GCC to produce an executable, this does not cause
#    the resulting executable to be covered by the GNU General Public License.
#    This exception does not however invalidate any other reasons why
#    the executable file might be covered by the GNU General Public License.
# 

# This file just make a stack frame for the contents of the .fini and
# .init sections.  Users may put any desired instructions in those
# sections.

# On the tricore the prolog is empty just define the symbols _init and _fini

	.file		"crti.s"

	.section	".init"
	.align 2
	.global	_init
_init:
	
		
	.section	".fini"
	.align	2
	.global	_fini
_fini:
	
	
# end of crti.s
