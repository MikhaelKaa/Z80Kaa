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
    call LCD1602
    jp (skip)

down
    call LCD1602_init
    jp (skip)
ok
    ld a, 0b00000000
    out (0xfe), A
    call delay100
    call delay100
    call delay100
    call delay100
    
    ld a, 0b00000001
    out (0xfe), A
skip
    ; Задержка.
    call delay100

    jr loop 

; Процедура вывода на экран LCD1602
LCD1602_init
    push af
    push bc
    ld a, 0x38
    call LCD1602_CMD
    ld a, 0x0c
    call LCD1602_CMD
    ld a, 0x06
    call LCD1602_CMD
    ld a, 0x01
    call LCD1602_CMD
    ld a, 0x80
    call LCD1602_CMD
    pop bc
    pop af
    ret

LCD1602
    push af
    push bc
    ld a, 'Z'
    call LCD1602_DATA
    ld a, '8'
    call LCD1602_DATA
    ld a, '0'
    call LCD1602_DATA
    ld a, ' '
    call LCD1602_DATA
    ld a, 'i'
    call LCD1602_DATA
    ld a, 's'
    call LCD1602_DATA
    ld a, ' '
    call LCD1602_DATA
    ld a, 'g'
    call LCD1602_DATA
    ld a, 'o'
    call LCD1602_DATA
    ld a, 'o'
    call LCD1602_DATA
    ld a, 'd'
    call LCD1602_DATA
    ld a, '!'
    call LCD1602_DATA
    ld a, ' '
    call LCD1602_DATA

    pop bc
    pop af
    ret

EBA
    push af
    push bc
    ld a, 'E'
    call LCD1602_DATA
    ld a, 'B'
    call LCD1602_DATA
    ld a, 'A'
    call LCD1602_DATA
    
    pop bc
    pop af
    ret


LCD1602_CMD
    call delay100
    push af
    ld a, 0b10000000
    out (0xfe), a

    call delay100
    pop af
    out (0xfd), a
    call delay100

    ;ld a, 0b00000000
    ;out (0xfe), a
    ret

LCD1602_DATA
    call delay100
    push af
    ld a, 0b10000100
    out (0xfe), a

    call delay100
    pop af
    out (0xfd), a
    call delay100

    ;ld a, 0b00000000
    ;out (0xfe), a

    ret

; Процедура задержки
delay100
    push af
    push bc
    ld bc, 1000
delay
    dec bc
    ld a, b
    or c
    jr nz, delay
    pop bc
    pop af
    ret

cnt db 0
portfe db 0


end:
    ; Выводим размер банарника.
    display "code size: ", /d, end - begin
    SAVEBIN "test.bin", begin, 32768; 32768 - размер бинарного файла для прошивки ПЗУ\ОЗУ