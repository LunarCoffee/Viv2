section .text

global read_scan_code
read_scan_code:
    xor eax, eax
    in al, 0x60
    ret