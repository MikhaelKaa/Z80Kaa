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

// RAM+ROM
output E,
output G,
output W,

// led
output led,

// LCD1602
output lcd_e,
output lcd_rw,
output lcd_rs

);

reg [4:0] clk_div;
always@(negedge in_clock) begin
	clk_div = clk_div + 1'b1;
	
end

// Z80 clock.
assign cpu_clock = clk_div[4];
//assign cpu_clock = reg_fe[0]?clk_div[4]:clk_div[3];

// M48Z35Y
assign E = mreq;
assign G = rd;
assign W = wr;


// io
wire IOWR = iorq | wr;
wire IORD = iorq | rd;


// testpin
reg [7:0] reg_fe = 8'b1;

always @(negedge IOWR or negedge rst) begin
	if(rst == 1'b0) begin
		reg_fe = 8'b0;
	end else
	if(adr == 3'b110) begin
		reg_fe = data;
	end
end

assign led = reg_fe[7];
assign lcd_e = ~(IOWR | ~(adr == 3'b101));
assign lcd_rw = reg_fe[1];
assign lcd_rs = reg_fe[2];

endmodule