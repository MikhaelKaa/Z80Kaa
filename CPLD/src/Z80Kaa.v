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

// led
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
	//prediv = 
end

// Z80 clock.
assign cpu_clock = clk_div[1];
//assign div =(reg_ff <= clk_div);
assign div = reg_fe[1]?(reg_ff >= clk_div):(1'b1);

assign intrpt = busrq?(~(clk_div == 0)):(1'b1);
//reg prediv = 1'b0;
/*always@(negedge ~(clk_div == 0)) begin
	preint <= ~preint;
end*/

// io
wire iowr = iorq | wr;
wire iord = iorq | rd;

//   port z80                        read        write
//wire port_0xf8 = (adr == 3'b000); // 
//wire port_0xf9 = (adr == 3'b001); // 
//wire port_0xfa = (adr == 3'b010); // 
//wire port_0xfb = (adr == 3'b011); // 
//wire port_0xfc = (adr == 3'b100); // lcd cmd 	 lcd cmd
//wire port_0xfd = (adr == 3'b101); // lcd data	 lcd data
//wire port_0xfe = (adr == 3'b110); // keyboard    reg_fe
//wire port_0xff = (adr == 3'b111); //				 div [3:0]
//wire port_0xfe = (adr[1:0] == 2'b10); // keyboard    reg_fe
//wire port_0xff = (adr[1:0] == 2'b11); //				 div [3:0]

wire port_lcd = /*adr[2] &*/ ~adr[1];

//wire kbd_rd = (iord | ~(port_0xfe));
wire kbd_rd = (iord | ~(/*adr[2] &*/ adr[1] & ~adr[0]));

assign KBD    = busrq?((kbd_rd)?(1'bz):(1'b0)):(1'bz); // fe

assign lcd_e  = busrq?(~(iowr) & port_lcd):(1'b0);  // fd
assign lcd_rw = busrq?(~adr[2]/*reg_fe[4]*/):(1'b0); //
assign lcd_rs = busrq?(adr[0]):(1'b1);

// register fe
reg [7:0] reg_fe = 8'b0;
// register ff
reg [7:0] reg_ff = 6'b0;


always @(negedge iowr /*or negedge rst*/) begin
	//if(rst == 1'b0) begin
		//reg_fe = 8'b0;
		//reg_ff = 4'b0111;
	//end else
	//if(port_0xfe) begin
	if((/*adr[2] &*/ adr[1] & ~adr[0])) begin
		reg_fe = data;
	end else
	//if(port_0xff) begin
	if((/*adr[2] &*/ adr[1] & adr[0])) begin
		reg_ff = data[7:0];
	end
end

assign led    = reg_fe[0];
assign gpio8    = reg_fe[2];
assign gpio9    = reg_fe[3];
endmodule