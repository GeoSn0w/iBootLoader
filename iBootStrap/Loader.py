import iBootStrap.SecureROM as SecureROM
import sys

DEBUG_WITHIN_IDA = 0


def dprint(string):
    if DEBUG_WITHIN_IDA or len(sys.argv) > 1:
        # Launching the script manually with args will trigger debug prints
        __builtins__.print(string)


print = dprint


def load_file(fd, neflags, format):
    fd.seek(0x0)
    bn = fd.read(0x4)
    fd.seek(0x200)
    ver_bin = fd.read(0x30)

    bitness = 1 if b'\xea' in bn else 2
    ver_str = ver_bin.decode()
    ver_str = "%s" % (ver_str)

    if ver_str[:9] == "SecureROM":
        SecureROM.process(fd, bitness)
