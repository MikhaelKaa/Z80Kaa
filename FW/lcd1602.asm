; Порт для отправки команд.
lcd_port_cmd   EQU 0xfc
; Порт для отправки данных.
lcd_port_data  EQU 0xfd
; Время задержки между обращениями к экрану, в попугаях.
lcd_delay_time EQU 8

; Процедура инициализвции LCD1602.
lcd_init
    ld hl, lcd_init_seq
    ld de, lcd_init_seq_end - lcd_init_seq ;5
lcd_init_loop
    ld a,(hl)
    out (lcd_port_cmd), a
    ld bc, lcd_delay_time
    call delay
    inc hl
    dec de
    ld a, d
    or e
    jr nz, lcd_init_loop
    ret

; Распечатает на экране нуль терминированную строку по адресу hl
lcd_print:
    ld a,(hl)
    and a
    ret z
    out (lcd_port_data), a
    ld bc, lcd_delay_time
    call delay
    inc hl
    jr lcd_print

lcd_put
    out (lcd_port_data), a
    ret

lcd_clear
    ld a, 1
    jp lcd_cmd

lcd_home
    ld a, 2
    jp lcd_cmd

;lcd_font1
    ;ld a, 0b00101000
    ;jp lcd_cmd

;lcd_font2
    ;ld a, 0b00101010
    ;jp lcd_cmd



lcd_set_cursor
    set 7, a
lcd_cmd
    out (lcd_port_cmd), a
    ret

lcd_print_num
    adc a, 48
    out (lcd_port_data), a
    ret

; a - адрес,
; hl - адрес 8 байт шрифта.
lcd_create
    and a, 7    ; Оставляем только 3 младщих бита
    rla
    rla
    rla
    add a, 0x40
    out (lcd_port_cmd), a
    ld bc, lcd_delay_time
    call delay
    ld de, 8
lcd_create_loop
    ld a,(hl)
    out (lcd_port_data), a
    ld bc, lcd_delay_time
    call delay
    inc hl
    dec de
    ld a, d
    or e
    jr nz, lcd_create_loop
    ;ld a, 0
    ;out (lcd_port_cmd), a
    ret

; https://maxpromer.github.io/LCD-Character-Creator/
;lcd_custom_char_0 db 0x09, 0x16, 0x0A, 0x15, 0x0E, 0x04, 0x04, 0x0E
lcd_custom_char_0 db 0x1F, 0x15, 0x1F, 0x04, 0x1F, 0x04, 0x0E, 0x0A
lcd_custom_char_1 db  0x00, 0x0A, 0x00, 0x1B, 0x00, 0x1B, 0x11, 0x15
lcd_custom_char_2 db 0x1F, 0x1F, 0x1F, 0x1F, 0x15, 0x00, 0x11, 0x1B

; Последовательность команд LCD1602 для инициализации дисплея.
lcd_init_seq: db 0x38, 0x0c, 0x06, 0x01, 0x80
lcd_init_seq_end:
; 0x38 - 00111000  длина блока данных 8 бит, две строки, 5*8 точек.
; 0x0c - 00001100  включение дисплея, курсор невидимый, моргание курсора отключено.
; 0x06 - 00000110  установка направления движения курсора вправо после ввода символа.
; 0x01 - 00000001  все символы стираются и адрес вводимого символа устанавливается в 0.
; 0x80 - 10000000  установка курсора в 0.
; http://avrprog.blogspot.com/2013/04/lcd1602com.html