#### BIOS ###
*** Interrupts list
    http://stanislavs.org/helppc
*** INT 0x13 Function 0x2 : to read sectors from disk into memory
    Call with   %ah = 0x2 : read function
                %al = number of sectors
                %ch = cylinder
                %cl = sector (bits 6-7 are high bits of "cylinder")
                %dh = head
                %dl = drive (0x80 for hard disk, 0x0 for floppy disk)
                %es:%bx = segment:offset of buffer
     Return:
                %al = 0x0 on success; err code on failure
*** INT 10H Function 0Eh : to write character in teletype mode
      %ah = 0xe : function write  
      %al = character
      %bh = page      
      %bl = foreground color (graphics modes)
      
      