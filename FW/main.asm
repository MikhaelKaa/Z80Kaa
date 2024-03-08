    ; указываем ассемблеру, что целевая платформа - spectrum48, хотя это и не так, но похуй...
    device ZXSPECTRUM48
    ;SIZE 32768
port_pwm  EQU 0xff


begin:
    org 0x0000
    ; Запрещаем прерывания.
    di
    ld bc, 8192
    call delay
    jp start

    org 0x0038 ; 56 
    di
    push af
    push bc
    push hl
    push de
    ;int programm
    call lcd_clear
    ld hl, Int_msg
    call lcd_print
    ld bc, 400
    call delay
    call test_sq
    
    ; end int programm
    ld bc, 65535
intdelay:
    dec bc
    ld a,b
    or c
    jr nz, intdelay
    pop de
    pop hl
    pop bc
    pop af
    ei
    reti

    org 0x0100
start:
    
    ; Устанавливаем дно стека.
    ld sp, 0x7ff7  ; M48T35, с часами.
    ;ld sp, 0x7fff ; M48Z35Y, без часов.
    ; Разрешаем прерывания.
    ei    

    ; Моргаем светодиодом
    ld a, 0 ; 0b00000000
    call port_fe_and_delay

    ld a, 0b00000001
    call port_fe_and_delay

    ld a, 0b00000000
    call port_fe_and_delay

    ld a, 0b00001111
    call port_fe_and_delay

    ld a, 0b00000000
    call port_fe_and_delay

    ld a, 0b00000001
    call port_fe_and_delay

    ; Включим ШИМ и отключим подсветку LCD1602
    ld a, 0b00001010
    out (0xfe), a

    ; Инициализация 1602
    call lcd_init

    ld bc, 500
    call delay

    ld hl, Hello_msg
    call lcd_print
    
    ;
    ld de, startup_end - startup
    ld hl, startup
    call test_pwm_loop

    call lcd_clear
    ld bc, 500
    call delay

    call game_init
    
main_loop:  
    
    call scan_keyboard
    call block_move
    call game_logic
    call hero_jump
    call draw_map

    ;call show_time
    
    ld bc, 655
    call delay
    call lcd_home

    ; Задержка.
    ld bc, 250
    call delay

    jp main_loop 


test_key_ok:
    ld hl, key_ok_msg
    call lcd_print
    ld bc, 60000
    call delay
    call lcd_clear
    ret

    ; Драйвер экрана
    include lcd1602.asm
    include m48t35.asm
    include keyboard.asm
    include game.asm
test_sq:
    ld de, 1024
.loop:
    ld a, e
    ;cpl
    out (port_pwm), a

    dec de
    ld a, d
    or e
    jr nz, test_sq.loop ; можно просто .loop 
    ret

test_pwm_loop:
    ld bc, 25
    nop
    nop
    nop
    nop    
    call delay

    ld a, (hl)
    out (port_pwm), a
    inc hl

    dec de
    ld a, d
    or e
    jr nz, test_pwm_loop
    ret

; Процедура задержки
delay:
    dec bc
    ld a, b
    or c
    jr nz, delay
    ret

; Запишет в порт 0xfe содержимое аккумулятора     
port_fe_and_delay
    out (0xfe), a
    ld bc, 20000
    call delay
    ret

; Различные переменные и константы.
Test_msg db "test message", 0
Hello_msg db "Z80Kaa board", 0
Int_msg db "interrupt", 0
warn_msg db "warning", 0
msg_startup db "startup", 0
msg_pre_ny db "C Hac", 0xbf, "y", 0xbe, "a", 0xc6, 0xe6, 0xb8, 0xbc, 0
key_ok_msg db "key ok", 0
msg db 0x74, 0x6f, 0x73, 0x79, 0x61, 0

cnt db 0

startup:
    incbin "tada.wav", 0x86
startup_end:

end:
    ; Выводим размер банарника.
    display "code size: ", /d, end - begin
    SAVEBIN "out.bin", begin, 32768; 32768 - размер бинарного файла для прошивки ПЗУ\ОЗУ