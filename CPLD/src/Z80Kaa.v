module Z80Kaa (
// Main clock generator
input in_clock,

// Z80 CPU
output cpu_clock,
inout	[7:0] data,
input [3:0] adr,
input rd,
input wr,
input iorq,
input mreq,
input m1,
input rst,


output E,
output G,
output W,

// testpin
output test0,
output test1

);

reg [2:0] clk_div;
always@(negedge in_clock) begin
	clk_div = clk_div + 1'b1;
	
end

// Z80 clock.
assign cpu_clock = clk_div[2];

// M48Z35Y
assign E = mreq;
assign G = rd;
assign W = wr;

// testpin
reg [1:0] testreg = 2'b0;

always @(negedge iorq | wr | adr[0]) begin
testreg = data[1:0];
end

assign test0 = testreg[0];
assign test1 = testreg[1];

endmodule