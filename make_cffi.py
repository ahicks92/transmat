import subprocess
import cffi
import sys

input_file = 'transmat.h'

if sys.platform == 'win32':
	command = 'cl'
	args = '/EP /DIS_TESTING ' + input_file
	lib = 'transmat.dll'
else:
	command  = 'cpp'
	args = '-D IS_TESTING ' + input_file
	lib = 'libtransmat.so'

src = subprocess.check_output(command + ' ' + args, shell = True)
src = src.replace("\r\n", "\n")
src = src.replace("#pragma once", "")
src = src.replace("__declspec(dllexport)", "")
ffi = cffi.FFI()
ffi.cdef(src)

transmat = ffi.dlopen("build/" + lib)
