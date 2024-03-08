; Переменные хнанящие состояние кнопок.
key_up db 0
key_down db 0
key_ok db 0

port_kb  EQU 0xfe

; Заполняет переменные в зависимости от того, нажата ли кнопка.
scan_keyboard:
    ; Очищаем переменные которые хранят состояние кнопок.
    xor a
    ld (key_ok), a
    ld (key_up), a
    ld (key_down), a

    ; Проверка кнопки ОК.
    in a, (port_kb)
    cp a, 0b11111110
    call z, ok
    ; Проверка кнопки Вверх.
    in a, (port_kb)
    cp a, 0b11111101
    call z, up
    ; Проверка кнопки Вниз.
    in a, (port_kb)
    cp a, 0b11111011
    call z, down
    ret
ok:
    ld a, 1
    ld (key_ok), a
    ret
up:
    ld a, 1
    ld (key_up), a
    ret
down:
    ld a, 1
    ld (key_down), a
    ret
