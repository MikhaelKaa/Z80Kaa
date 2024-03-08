map1: db "#              #", 0
map1_end
map2: db "#              #", 0
map2_end
game_cnt_block: db 0
game_cnt_move: db 0
game_block_coord: db 0
game_vars_end

map_init: db "#              #", 0


game_init:
    ld hl, map1
    ld bc, game_vars_end - map1
    xor a  ;ld a, 0
clear_map_loop:
    ld (hl), a
    inc hl
    
    dec bc
    ld a,b
    or c
    jr nz, clear_map_loop

    ld hl, map_init
    ld de, map1
    ld bc, map1_end-map1
    ldir

    ld hl, map_init
    ld de, map2
    ld bc, map2_end-map2
    ldir

    ret

draw_map:
    ld hl, map1
    call lcd_print
    call lcd_newline
    ld bc, 200
    call delay
    ld hl, map2
    call lcd_print
    ret

block_move:
    ld a, (key_up)
    cp a, 1
    ret nz
    ; key up is pessed
    ld hl, game_block_coord
    ld (hl), 8
    call draw_block
    ret

hero_jump:
    ld a, (key_ok)
    cp a, 1
    jr nz, .ok_not_press

    ; key is pessed
    ld hl, map1+3
    ld a, "@"
    ld (hl), a
    ld hl, map2+3
    ld a, " "
    ld (hl), a
    ret

.ok_not_press:
    ; key not pressed

    ld hl, map2+3
    ld a, "@"
    ld (hl), a

    ld hl, map1+3
    ld a, " "
    ld (hl), a
    ret

game_logic:
    ; dec (hl)
    ; ld hl, game_block_coord
    ; call draw_block
    ; ld bc, 6553
    ; call delay

    ld hl, game_cnt_block
    inc (hl)
    ld a, (hl)
    cp a, 0
    jr nz, .game_cnt_is_null

    ; Генерируем новое препятствие
    ld hl, game_block_coord
    ld (hl), 10
    ret

.game_cnt_is_null
    ld hl, map2+5
    ld a, " "
    ld (hl), a
    ret

; Отрисовка блока (кактуса)
draw_block:
    push hl
    push bc
    ld hl, (game_block_coord)
    ld bc, map2
    add hl, bc
    ld a, '#'
    ld (hl), a

    pop bc
    pop hl
    ret
