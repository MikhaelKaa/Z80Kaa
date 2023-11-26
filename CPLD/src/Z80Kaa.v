module Z80Kaa (
// Main clock generator
input in_clock,

// Z80 CPU
output cpu_clock,
inout	[7:0] data,
input [2:0] adr,
input a9,
input rd,
input wr,
input iorq,
input mreq,
input m1,
input rst,

// enable
input busrq,

// led
output led,

// LCD1602
output lcd_e,
output lcd_rw,
output lcd_rs,

// Keyboard
output KBD,

// div
output div
);

reg [3:0] clk_div = 4'b0;
reg [3:0] clk_cnt = 4'b0;
always@(negedge in_clock) begin
	clk_div = clk_div + 1'b1;
	if (reg_ff == clk_cnt) begin
		pre_div = ~pre_div;
		clk_cnt = 0;
	end
	else clk_cnt = clk_cnt + 1'b1;
end

// Z80 clock.
assign cpu_clock = clk_div[1];
//assign cpu_clock = clk_div[reg_ff];
//assign cpu_clock = reg_ff[0]?clk_div[3]:clk_div[2];

reg pre_div = 1'b0;
assign div = pre_div;
// io
wire iowr = iorq | wr;
wire iord = iorq | rd;

//   port z80                        read        write
wire port_0xf8 = (adr == 3'b000); // 
wire port_0xf9 = (adr == 3'b001); // 
wire port_0xfa = (adr == 3'b010); // 
wire port_0xfb = (adr == 3'b011); // 
wire port_0xfc = (adr == 3'b100); // lcd cmd 	 lcd cmd
wire port_0xfd = (adr == 3'b101); // lcd data	 lcd data
wire port_0xfe = (adr == 3'b110); // keyboard    reg_fe
wire port_0xff = (adr == 3'b111); //				 div [3:0]

wire port_lcd = adr[2] & ~adr[1];

wire kbd_rd = (iord | ~(port_0xfe));
assign KBD    = busrq?((kbd_rd)?(1'bz):(1'b0)):(1'bz); // fe

assign lcd_e  = busrq?(~(iowr) & port_lcd):(1'b0);  // fd
assign lcd_rw = busrq?(1'b0):(1'b0); // TODO Write only
assign lcd_rs = busrq?(adr[0]):(1'b1);

// register fe
reg [7:0] reg_fe = 8'b0;
// register ff
reg [3:0] reg_ff = 4'b0;


always @(negedge iowr or negedge rst) begin
	if(rst == 1'b0) begin
		reg_fe = 8'b0;
		reg_ff = 4'b0011;
	end else
	if(port_0xfe) begin
		reg_fe = data;
	end else
	if(port_0xff) begin
		reg_ff = data[3:0];
	end
end

assign led    = /*busrq?(*/reg_fe[0]/*):(1'b1)*/;

// M48Z35Y
//assign E = mreq;
//assign G = rd;
//assign W = wr;

endmodule