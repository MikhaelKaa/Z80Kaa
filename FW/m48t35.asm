set_time:
    ld a, 0b10000000 ; Enable time set
    ld (0x7ff8), a
    ld bc, 20
    call delay

    ld a, 0x55 ; Seconds
    ld (0x7ff9), a

    ld a, 0x46 ; Minutes
    ld (0x7ffa), a  

    ld a, 0x21 ; Hours
    ld (0x7ffb), a  

    ld a, 0b00000000 ; Disable time set
    ld (0x7ff8), a
    ld bc, 20
    call delay
    ret

show_time:
    ld a, (0x7ffb)
    rra
    rra
    rra
    rra
    and a, 0b00000011
    call lcd_print_num  
    ld bc, 10
    call delay
    
    ld a, (0x7ffb)
    and a, 0b00001111
    call lcd_print_num
    ld bc, 10
    call delay

    ld a, 0x3a
    call lcd_put
    ld bc, 10
    call delay

    ld a, (0x7ffa)
    rra
    rra
    rra
    rra
    and a, 0b00000111
    call lcd_print_num  
    ld bc, 10
    call delay
    
    ld a, (0x7ffa)
    and a, 0b00001111
    call lcd_print_num
    ld bc, 10
    call delay

    ld a, 0x3a
    call lcd_put
    ld bc, 10
    call delay

    ld a, (0x7ff9)
    rra
    rra
    rra
    rra
    and a, 0b00000111
    call lcd_print_num  
    ld bc, 20
    call delay
    
    ld a, (0x7ff9)
    and a, 0b00001111
    call lcd_print_num
    ld bc, 20
    call delay
    ret