module Z80Kaa (
// Main clock generator
input in_clock, // 24MHz

// Z80 CPU
output cpu_clock,
input	[7:0] data,
input [2:0] adr,
input a9,
input rd,
input wr,
input iorq,
input mreq,
input m1, 
input rst,
output intrpt,
// enable
input busrq,

// led & gpio
output led,
output gpio8,
output gpio9,

// LCD1602
output lcd_e,
output lcd_rw,
output lcd_rs,

// Keyboard
output KBD,

// div
output div
);

reg [7:0] clk_div = 8'b0;
always@(negedge in_clock) begin
	clk_div = clk_div + 1'b1;
end

// Z80 clock.
assign cpu_clock = clk_div[1];

assign div = reg_fe[1]?(reg_ff >= clk_div):(1'b1);

assign intrpt = busrq?(~(clk_div == 0)):(1'b1);

// io
wire iowr = iorq | wr;
wire iord = iorq | rd;

wire port_lcd =  ~adr[1];

wire kbd_rd = (iord | ~(adr[1] & ~adr[0]));

assign KBD    = busrq?((kbd_rd)?(1'bz):(1'b0)):(1'bz); // fe

assign lcd_e  = busrq?(~(iowr) & port_lcd):(1'b0);  // fd
assign lcd_rw = busrq?(~adr[2]):(1'b0); //
assign lcd_rs = busrq?(adr[0]):(1'b1);

// register fe
reg [7:0] reg_fe = 8'b0;
// register ff
reg [7:0] reg_ff = 8'b0;


always @(negedge iowr) begin

	if((adr[1] & ~adr[0])) begin
		reg_fe = data;
	end else
	if((adr[1] & adr[0])) begin
		reg_ff = data;
	end
end

assign led    = reg_fe[0];
assign gpio8    = reg_fe[2];
assign gpio9    = reg_fe[3];
endmodule