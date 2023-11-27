; Порт для отправки команд.
lcd_port_cmd   EQU 0xfc
; Порт для отправки данных.
lcd_port_data  EQU 0xfd
; Время задержки между обращениями к экрану, в попугаях.
lcd_delay_time EQU 8

; Процедура инициализвции LCD1602.
lcd_init
    ld hl, lcd_init_seq
    ld bc, 5
lcd_init_loop
    ld a,(hl)
    out (lcd_port_cmd), a
    push bc
    ld bc, lcd_delay_time
    call delay_bc
    inc hl
    pop bc
    dec bc
    ld a, b
    or c
    jr nz, lcd_init_loop
    ret

; Распечатает на экране нуль терминированную строку по адресу hl
lcd_print
    ld a,(hl)
    and a
    ret z
    out (lcd_port_data), a
    ld bc, lcd_delay_time
    call delay_bc
    inc hl
    jr lcd_print

lcd_clear
    ld a, 1
    jp lcd_cmd

lcd_home
    ld a, 2
    jp lcd_cmd

lcd_set_cursor
    set 7, a
lcd_cmd
    out (lcd_port_cmd), a
    ret

; Последовательность команд LCD1602 для инициализации дисплея.
lcd_init_seq db 0x38, 0x0c, 0x06, 0x01, 0x80
; 0x38 - 00111000  длина блока данных 8 бит, две строки, 5*8 точек.
; 0x0c - 00001100  включение дисплея, курсор невидимый, моргание курсора отключено.
; 0x06 - 00000110  установка направления движения курсора вправо после ввода символа.
; 0x01 - 00000001  все символы стираются и адрес вводимого символа устанавливается в 0.
; 0x80 - 10000000  установка курсора в 0.
; http://avrprog.blogspot.com/2013/04/lcd1602com.html