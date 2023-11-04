    ; указываем ассемблеру, что целевая платформа - spectrum128(pentagon)
    device none

    SIZE 32768
    OUTPUT "test.bin",t  

    ; адрес на который компилировать
    org 0x1000
    
begin_file:
    ; запрещаем прерывания
    di
    ; устанавливаем дно стека
    ld sp,#6100
    ; ld hl,#DEC0:push hl
    ld a,0
loop:
    ;выводим в порт 0xFE  
    inc a
    out (#fe),a
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    
    nop:nop:nop; nop:nop:nop занимает столько же тактов, что и jr n (12)
    
    ;выводим в порт 0xFE  
    inc a
    out (#fe),a

    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
 
    jr loop
    
end_file:
    ; выводим размер банарника
    display "code size: ", /d, end_file - begin_file

