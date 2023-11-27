    ; указываем ассемблеру, что целевая платформа - spectrum48, хотя это и не так, но похуй...
    device ZXSPECTRUM48
    ;SIZE 32768
begin:
    org 0x0000
    ; Запрещаем прерывания.
    di
    jp start

    org 0x0038
    di
    push af
    push bc
    push hl
    ;int programm
    call lcd_clear
    ld hl, Int_msg
    ld bc, 400
    call delay
    call lcd_print
    ; end int programm
    ld bc, 256
intdelay
    dec bc
    ld a,b
    or c
    jr nz, intdelay
    pop hl
    pop bc
    pop af
    ei
    reti

    org 0x0100 
start
    ; Устанавливаем дно стека.
    ld sp, 0x7fff
    ; Разрешаем прерывания.
    ei    

    ld a, 0b00000000
    out (0xfe), a
    ld bc, 40000
    call delay

    ld a, 0b00000001
    out (0xfe), a
    ld bc, 40000
    call delay

    ld a, 0b00000000
    out (0xfe), a
    ld bc, 40000
    call delay

    ld a, 0b00000001
    out (0xfe), a
    ld bc, 40000
    call delay

    call lcd_init
    ld bc, 500
    call delay
    ld hl, Hello_msg
    call lcd_print

loop:
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
    ;ld hl, Test_msg
    ;call lcd_print 
    ld hl, lcd_custom_char_0
    ld a, 0
    call lcd_create
    ld bc, 100
    call delay
    ld hl, lcd_custom_char_1
    ld a, 1
    call lcd_create
    jp (skip)

down
    ;call lcd_clear
    ld a, 0
    call lcd_put
    ld bc, 100
    call delay
    ld a, 1
    call lcd_put   
    jp (skip)
ok
    call lcd_clear

    ;ld a, 40
    ;call lcd_set_cursor
    
    ;ld a, (cnt)
    ;dec a
    ;ld (cnt), a
    ;out (0xff), a
    ;ld bc, 4000
   ; call delay_bc
skip
    ; Задержка.
    ld bc, 25000
    call delay

    jr loop 

    ; Драйвер экрана
    include lcd1602.asm

; Процедура задержки
delay
    dec bc
    ld a, b
    or c
    jr nz, delay
    ret

; Различные переменные и константы.
Test_msg db "test message", 0
Hello_msg db "Z80Kaa board", 0
Int_msg db "interrupt", 0
warn_msg db "warning", 0

cnt db 0

end:
    ; Выводим размер банарника.
    display "code size: ", /d, end - begin
    SAVEBIN "out.bin", begin, 32768; 32768 - размер бинарного файла для прошивки ПЗУ\ОЗУ