from iBootStrap.Symbolicate import *
from ida_auto import *
from ida_segment import *
import idc_bc695
import idc
import ida_funcs
from idaapi import *
import idaapi
import ida_search

symtab = {
    0x00000000: 'start',
    0x00000040: 'reset',
    0x00000300: 'Description',
    0x00000304: 'ReleaseCategory',
    0x00000308: 'iBootVersion',
    0x0000030C: 'main',
    0x00000310: 'Start',
    0x0000031C: 'sram_start',
    0x00000334: 'heap_base'
}

jumpref = {
    0x00000004: 'arm_undefined',
    0x00000008: 'arm_syscall',
    0x0000000C: 'arm_prefetch_abort',
    0x00000010: 'arm_data_abort',
    0x00000014: 'arm_reserved',
    0x00000018: 'arm_irq',
    0x0000001C: 'arm_fiq'
}

string_start = None
string_end = None


def process(fd, bitness):
    enable_auto(False)
    base_addr = 0x0
    if bitness == 1:
        idaapi.set_processor_type('ARM:ARMv7-A', idaapi.SETPROC_ALL | idaapi.SETPROC_FATAL)
        idaapi.get_inf_structure().lflags |= idaapi.LFLG_PC_FLAT
    elif bitness == 2:
        idaapi.set_processor_type("arm", idaapi.SETPROC_LOADER_NON_FATAL)
        idaapi.get_inf_structure().lflags |= idaapi.LFLG_64BIT

    fd.seek(0, idaapi.SEEK_END)
    size = fd.tell()
    segm = idaapi.segment_t()
    segm.bitness = bitness
    segm.start_ea = 0
    segm.end_ea = size

    if base_addr != 0:
        print("[*] Rebasing to address 0x%x" % (base_addr))
        idaapi.rebase_program(base_addr, MSF_NOFIX)
        idaapi.autoWait()

    idaapi.add_segm_ex(segm, "SecureROM", "CODE", idaapi.ADDSEG_OR_DIE)

    fd.seek(0)
    fd.file2base(0, 0, size, False)
    print("[*] Pass One")
    print("[*] Defining functions")
    #locate_functions(segm)
    print("[*] Defining early initialation instructions")
    build_jump_table(segm)
    print("[*] Attempting to force string definitons")
    global string_start, string_end
    string_start, string_end = process_strings(segm)
    print("[*] Pass Two")
    print("[*] Hunting for and defining symbols")
    symbolicate(segm)


# ------
# Initial Analysis
# ------

def reanalyze(segm):
    AnalyzeArea(segm.start_ea, segm.end_ea)
    idaapi.autoWait()


def build_jump_table(segm):
    idaapi.add_entry(0, 0, "start", 1)
    if segm.bitness == 1:
        MakeFunction(0x0, 0x1C)


def locate_functions(segm):
    ss = find_probable_string_start(segm)
    print("[+] Strings = %s" % ss)
    for i in ["7F 23 03 D5", "BD A9", "BF A9"]:
        ea = segm.start_ea
        while ea != BADADDR:
            ea = ida_search.find_binary(ea, segm.end_ea, i, 16, ida_search.SEARCH_DOWN)
            if ea != BADADDR and ea <= ss:
                ea -= 2

                if (ea % 4) == 0 and idaapi.get_full_flags(ea) < 0x200:
                    # print("[+] Defining a function at 0x%x" % (ea))
                    ida_funcs.add_func(ea)

                ea += 4


def process_strings(segm):
    # If you jump to the bottom of the file and search upwards for this hex, you'll get the string section start
    string_addr = find_probable_string_start(segm)
    if string_addr == BADADDR:
        print("[-] Failed to find string information. Not much info can be pulled.")
        return BADADDR, ida_search.find_binary(0x0, segm.end_ea, "41 70 70 6C 65 20 49", 16, ida_search.SEARCH_DOWN)

    strend = ida_search.find_binary(string_addr, segm.end_ea, "41 70 70 6C 65 20 49", 16,
                                    ida_search.SEARCH_DOWN)  # 'Apple, I'
    ea = string_addr
    if strend == BADADDR:
        strend = string_addr + 0xFF

    # Best we can do here is just tell ida to make every single byte, individually, a string; it figures it out.
    for i in range(ea, strend):
        idc.create_strlit(i, BADADDR)

    idc.create_strlit(strend, BADADDR)  # Create the "Apple, Inc." String

    return string_addr, strend


# ------
# Segmentation
# ------

def seg(fd, segm, ss, se, ft, lf):
    base = segm.start_ea
    del_segm(segm.start_ea)
    text = idaapi.segment_t()
    text.bitness = 1  # 32-bit
    text.end_ea = lf + 0x8
    text.start_ea = base

    idaapi.add_segm_ex(text, "__text", "CODE", idaapi.ADDSEG_OR_DIE)


# ------
# Symbolication 
# ------

def symbolicate(segm):
    find_string_ref("", segm.start_ea)
