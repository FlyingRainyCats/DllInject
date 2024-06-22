; Generated ASM code from bytes
PUBLIC WoW64_CreateRemoteThread
.386
.model flat, c

.code
.safeseh SEH_handler
SEH_handler proc
 ret
SEH_handler   endp

WoW64_CreateRemoteThread PROC
db   055h, 089h, 0e5h, 06ah, 033h, 0e8h, 051h, 002h, 000h, 000h, 055h, 048h, 089h, 0e5h, 048h, 083h
db   0e4h, 0f0h, 048h, 083h, 0ech, 048h, 08bh, 04dh, 010h, 08bh, 055h, 014h, 04dh, 031h, 0c0h, 0e8h
db   018h, 000h, 000h, 000h, 0c9h, 0e8h, 032h, 002h, 000h, 000h, 089h, 0ech, 089h, 0e4h, 089h, 0e2h
db   068h, 068h, 065h, 06ch, 06ch, 068h, 06fh, 06ch, 06ch, 06fh, 05dh, 0c3h, 048h, 08bh, 0c4h, 048h
db   089h, 058h, 008h, 048h, 089h, 070h, 010h, 048h, 089h, 078h, 018h, 055h, 041h, 054h, 041h, 055h
db   041h, 056h, 041h, 057h, 048h, 08dh, 068h, 0a1h, 048h, 081h, 0ech, 090h, 000h, 000h, 000h, 065h
db   048h, 08bh, 004h, 025h, 030h, 000h, 000h, 000h, 041h, 0b9h, 04eh, 000h, 000h, 000h, 044h, 08bh
db   0e1h, 04dh, 08bh, 0f0h, 045h, 033h, 0edh, 044h, 08bh, 0fah, 0c7h, 045h, 01fh, 04eh, 000h, 054h
db   000h, 048h, 08bh, 048h, 060h, 041h, 08dh, 079h, 0d2h, 0c7h, 045h, 023h, 044h, 000h, 04ch, 000h
db   0c7h, 045h, 027h, 04ch, 000h, 02eh, 000h, 0c7h, 045h, 02bh, 044h, 000h, 04ch, 000h, 048h, 08bh
db   059h, 018h, 048h, 003h, 0dfh, 0c7h, 045h, 02fh, 04ch, 000h, 000h, 000h, 04ch, 08bh, 003h, 04ch
db   03bh, 0c3h, 00fh, 084h, 07dh, 001h, 000h, 000h, 041h, 00fh, 0b7h, 048h, 038h, 049h, 08bh, 040h
db   040h, 048h, 0d1h, 0e9h, 048h, 08dh, 014h, 048h, 0ebh, 004h, 048h, 083h, 0eah, 002h, 066h, 083h
db   07ah, 0feh, 05ch, 075h, 0f5h, 048h, 08dh, 045h, 01fh, 04ch, 08dh, 055h, 01fh, 048h, 03bh, 0d0h
db   074h, 05ah, 041h, 00fh, 0b7h, 0c9h, 044h, 00fh, 0b7h, 01ah, 045h, 00fh, 0b7h, 0cbh, 066h, 044h
db   02bh, 0cfh, 041h, 08dh, 043h, 09fh, 066h, 083h, 0f8h, 019h, 08dh, 041h, 09fh, 066h, 045h, 00fh
db   047h, 0cbh, 066h, 083h, 0f8h, 019h, 077h, 003h, 066h, 02bh, 0cfh, 066h, 044h, 03bh, 0c9h, 075h
db   014h, 066h, 045h, 085h, 0c9h, 074h, 025h, 048h, 083h, 0c2h, 002h, 049h, 083h, 0c2h, 002h, 041h
db   00fh, 0b7h, 00ah, 0ebh, 0c1h, 04dh, 08bh, 000h, 04ch, 03bh, 0c3h, 00fh, 084h, 004h, 001h, 000h
db   000h, 041h, 0b9h, 04eh, 000h, 000h, 000h, 0e9h, 07ch, 0ffh, 0ffh, 0ffh, 049h, 08bh, 048h, 020h
db   048h, 085h, 0c9h, 00fh, 084h, 0ech, 000h, 000h, 000h, 048h, 063h, 041h, 03ch, 044h, 088h, 06dh
db   017h, 0c7h, 045h, 00bh, 065h, 061h, 074h, 065h, 0c7h, 045h, 007h, 04eh, 074h, 043h, 072h, 08bh
db   094h, 008h, 088h, 000h, 000h, 000h, 0c7h, 045h, 013h, 061h, 064h, 045h, 078h, 0c7h, 045h, 00fh
db   054h, 068h, 072h, 065h, 048h, 003h, 0d1h, 074h, 05bh, 04ch, 063h, 052h, 01ch, 04ch, 063h, 05ah
db   024h, 04ch, 003h, 0d1h, 048h, 063h, 05ah, 020h, 04ch, 003h, 0d9h, 08bh, 072h, 018h, 048h, 003h
db   0d9h, 041h, 08bh, 0d5h, 085h, 0f6h, 074h, 03ch, 08bh, 0fah, 04ch, 08dh, 045h, 007h, 04ch, 08dh
db   04dh, 007h, 048h, 063h, 004h, 0bbh, 048h, 003h, 0c1h, 04ch, 03bh, 0c0h, 074h, 02dh, 048h, 085h
db   0c0h, 074h, 01bh, 041h, 0b0h, 04eh, 044h, 038h, 000h, 075h, 013h, 045h, 084h, 0c0h, 074h, 01bh
db   049h, 0ffh, 0c1h, 048h, 0ffh, 0c0h, 045h, 08ah, 001h, 044h, 03ah, 000h, 074h, 0edh, 0ffh, 0c2h
db   03bh, 0d6h, 072h, 0c4h, 0b8h, 002h, 000h, 000h, 0f0h, 0ebh, 05fh, 041h, 00fh, 0b7h, 004h, 07bh
db   04dh, 063h, 014h, 082h, 04ch, 003h, 0d1h, 074h, 0ebh, 04ch, 089h, 06ch, 024h, 050h, 048h, 08dh
db   04dh, 07fh, 04ch, 089h, 06ch, 024h, 048h, 04dh, 08bh, 0cch, 04ch, 089h, 06ch, 024h, 040h, 045h
db   033h, 0c0h, 04ch, 089h, 06ch, 024h, 038h, 0bah, 000h, 000h, 000h, 010h, 044h, 089h, 06ch, 024h
db   030h, 04ch, 089h, 06ch, 024h, 028h, 04ch, 089h, 07ch, 024h, 020h, 04ch, 089h, 06dh, 07fh, 041h
db   0ffh, 0d2h, 085h, 0c0h, 078h, 014h, 04dh, 085h, 0f6h, 074h, 006h, 08bh, 045h, 07fh, 041h, 089h
db   006h, 033h, 0c0h, 0ebh, 005h, 0b8h, 001h, 000h, 000h, 0f0h, 04ch, 08dh, 09ch, 024h, 090h, 000h
db   000h, 000h, 049h, 08bh, 05bh, 030h, 049h, 08bh, 073h, 038h, 049h, 08bh, 07bh, 040h, 049h, 08bh
db   0e3h, 041h, 05fh, 041h, 05eh, 041h, 05dh, 041h, 05ch, 05dh, 0c3h, 0cbh, 0c7h, 044h, 024h, 004h
db   023h, 000h, 000h, 000h, 0cbh

WoW64_CreateRemoteThread ENDP
END

