    ; указываем ассемблеру, что целевая платформа - spectrum48, хотя это и не так, но похуй...
    device ZXSPECTRUM48
    ;SIZE 32768
begin:
    org 0x0000
    ; Запрещаем прерывания.
    di
    jp start

    org 0x0038
    jp interrupt
        
interrupt
    di
    push af
    push bc
    ;int programm
    ld a, 0b00000000
    out (0xfe), a
    ld bc, 1000
    call delay_bc

    ld a, 0b00000001
    out (0xfe), a
    ld bc, 1000
    call delay_bc

    ld a, 0b00000000
    out (0xfe), a
    ld bc, 1000
    call delay_bc

    ld a, 0b00000001
    out (0xfe), a
    ld bc, 1000
    call delay_bc
    ; end int programm
    ld bc, 256
intdelay
    dec bc
    ld a,b
    or c
    jr nz, intdelay
    pop bc
    pop af
    ei
    reti

    org 0x0100
start:
    ; Устанавливаем дно стека.
    ld sp, 0x7fff
    ; Разрешаем прерывания.
    ei    
    ld a,0

    ld a, 0b00000000
    out (0xfe), a
    ld bc, 4000
    call delay_bc

    ld a, 0b00000001
    out (0xfe), a
    ld bc, 4000
    call delay_bc

    ld a, 0b00000000
    out (0xfe), a
    ld bc, 4000
    call delay_bc

    ld a, 0b00000001
    out (0xfe), a
    ld bc, 4000
    call delay_bc

    ;call LCD1602_init
loop:
    ; Увеличиваем регистр а.
    ;inc a
    ;ld a, (cnt)
    ; Выводим в порт 0xFE.


    in a, (0xfe)
    cp a, 0b11111101
    jp z, up

    in a, (0xfe)
    cp a, 0b11111011
    jp z, down

    in a, (0xfe)
    cp a, 0b11111110
    jp z, ok

    jp (skip)

up
    ld hl, Text
    call print1602_hl  ;LCD1602
    jp (skip)

down
    call lcd_init;LCD1602_init
    jp (skip)
ok
    ld a, (cnt)
    dec a
    ld (cnt), a
    out (0xff), a
    ld bc, 4000
    call delay_bc
skip
    ; Задержка.
    ld bc, 25000
    call delay_bc

    jr loop 

; Процедура инициализвции LCD1602
lcd_init
    ld hl, lcd_init_seq
    ld bc, 5
lcd_init_loop
    ld a,(hl)
    out (0xfc), a
    push bc
    ld bc, 300
    call delay_bc
    inc hl
    pop bc
    dec bc
    ld a, b
    or c
    jr nz, lcd_init_loop
    ret

lcd_init_seq db 0x38, 0x0c, 0x06, 0x01, 0x80

print1602_hl
    ld a,(hl)
    and a
    ret z
    out (0xfd), a
    ld bc, 300
    call delay_bc
    inc hl
    jr print1602_hl

Text db "Z80Kaa board ", 0

; Процедура задержки
delay_bc
    push af
    ;push bc
delay_loop
    dec bc
    ld a, b
    or c
    jr nz, delay_loop
    ;pop bc
    pop af
    ret

cnt db 0
;portfe db 0

end:
    ; Выводим размер банарника.
    display "code size: ", /d, end - begin
    SAVEBIN "test.bin", begin, 32768; 32768 - размер бинарного файла для прошивки ПЗУ\ОЗУ