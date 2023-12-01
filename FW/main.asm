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

    ld a, 0b00001111
    out (0xfe), a
    ld bc, 40000
    call delay

    ld a, 0b00000000
    out (0xfe), a
    ld bc, 40000
    call delay

    ld a, 0b00001111
    out (0xfe), a
    ld bc, 40000
    call delay

    call lcd_init
    ld bc, 500
    call delay
    ld hl, Hello_msg
    call lcd_print

loop:
    in a, (port_kb)
    cp a, 0b11111101
    jp z, up

    in a, (port_kb)
    cp a, 0b11111011
    jp z, down

    in a, (port_kb)
    cp a, 0b11111110
    jp z, ok

    jp (skip)

up
    ld a, (cnt)
    inc a
    ld (cnt), a
    out (port_pwm), a
    ld bc, 400
    call delay
    jp (skip)

down
    ld a, (cnt)
    dec a
    ld (cnt), a
    out (port_pwm), a
    ld bc, 400
    call delay

    jp (skip)
ok
    call lcd_clear

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
msg db 0x74, 0x6f, 0x73, 0x79, 0x61, 0


menu_obj defw menu_obj_0
menu defw menu_obj_0, menu_obj_1, menu_obj_2, 0
menu_obj_0 defw menu_0
menu_obj_0_text db "menu_0", 0
menu_0

    ret

menu_obj_1 defw menu_1
menu_obj_1_text db "menu_1", 0
menu_1

    ret

menu_obj_2 defw menu_2
menu_obj_2_text db "menu_2", 0
menu_2

    ret
port_pwm  EQU 0xff
port_kb  EQU 0xfe
cnt db 0

end:
    ; Выводим размер банарника.
    display "code size: ", /d, end - begin
    SAVEBIN "out.bin", begin, 32768; 32768 - размер бинарного файла для прошивки ПЗУ\ОЗУ