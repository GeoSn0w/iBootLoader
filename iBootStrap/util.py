from ida_search import *
from idautils import *
from idc import *

SROM = 0
IBOT = 1
SEP = 2

segmbitness = None
filetype = None
buildtype = None
ibootversion = None
issep = None


def bad(ea):
    return ea == BADADDR


def is64(segm):
    return segm.bitness == 2


def find_probable_string_start(segm):
    # The initial run of this function is before any analysis or segmentation starts.
    #
    # functions = list(Functions())

    prologue = "6E 6F 72 30 00"

    # if string_addr < functions[len(functions)-1]:
    if filetype == SROM:
        prologue = "6E 6F 72 30 00"

    string_addr = find_binary(segm.end_ea, segm.start_ea, prologue, 16, SEARCH_UP)

    return string_addr
