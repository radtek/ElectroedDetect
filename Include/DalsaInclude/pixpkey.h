//
// Pixel Processor File Key Name definitions.
//

#ifndef _PIXPKEY_H_
#define _PIXPKEY_H_

#define PIXP_FILE_EXT						"CPI"

#define PIXPSECTION_GENERAL					"General"
#define PIXPSECTION_CONFIG					"Config_"
#define PIXPSECTION_BUFFER					"Buffer_"
#define PIXPSECTION_PIXEL					"Pixel_"
#define PIXPSECTION_ON_DEMAND				"On-Demand_"

/* General	*/
#define PIXPKEY_CPI_VERSION					"Version"
#define PIXPKEY_DESIGN_NAME					"Design Name"
#define PIXPKEY_DESIGN_NUMBER				"Design Number"
#define PIXPKEY_CORE_FPGA					"Core FPGA"
#define PIXPKEY_CTRL_FPGA					"Ctrl FPGA"
#define PIXPKEY_MAX_CORE_REG				"Max Core Reg"
#define PIXPKEY_MAX_CTRL_REG				"Max Ctrl Reg"
#define PIXPKEY_MAX_DPT						"Max DPT"
#define PIXPKEY_DEFAULT_CONFIG				"Default Config"
#define PIXPKEY_FPGA_CORE_ID				"Core ID"
#define PIXPKEY_FPGA_CTRL_ID				"Ctrl ID"
#define PIXPKEY_FPGA_CORE_SPEED				"Core Speed"
#define PIXPKEY_FPGA_CTRL_SPEED				"Ctrl Speed"
#define PIXPKEY_FPGA_CORE_DEVICE			"Core Device"
#define PIXPKEY_FPGA_CTRL_DEVICE			"Ctrl Device"
#define PIXPKEY_FRAME_BUFFER_BANK0 			"Frame Buffer Bank 0"
#define PIXPKEY_FRAME_BUFFER_BANK1 			"Frame Buffer Bank 1"
#define PIXPKEY_FRAME_BUFFER_BANK2 			"Frame Buffer Bank 2"
#define PIXPKEY_FRAME_BUFFER_BANK3 			"Frame Buffer Bank 3"
#define PIXPKEY_LINE_BUFFER_BANK0 			"Line Buffer Bank 0"
#define PIXPKEY_LINE_BUFFER_BANK1 			"Line Buffer Bank 1"
#define PIXPKEY_LINE_BUFFER_BANK2 			"Line Buffer Bank 2"
#define PIXPKEY_LINE_BUFFER_BANK3 			"Line Buffer Bank 3"


/* Config	*/
#define PIXPKEY_CONFIG_NAME				"Name"
#define PIXPKEY_DPT							"DPT_"
#define PIXPKEY_CORE_REG					"Core_Reg_"
#define PIXPKEY_CTRL_REG					"Ctrl_Reg_"
#define PIXPKEY_INPUT_FORMAT				"Input Format"
#define PIXPKEY_INPUT_FRAME				"Input Frame"
#define PIXPKEY_INPUT_FIELD_ORDER		"Input Field Order"
#define PIXPKEY_INPUT_WIDTH				"Input Width"
#define PIXPKEY_INPUT_HEIGHT				"Input Height"
#define PIXPKEY_OUTPUT_FORMAT				"Output Format"
#define PIXPKEY_OUTPUT_FRAME				"Output Frame"
#define PIXPKEY_OUTPUT_WIDTH				"Output Width"
#define PIXPKEY_OUTPUT_HEIGHT				"Output Height"
#define PIXPKEY_OUTPUT_FIELD_ORDER		"Output Field Order"
#define PIXPKEY_SNAP_COUNT					"Snap Count"
#define PIXPKEY_INTERRUPT					"Interrupt"
#define PIXPKEY_WAIT_STATE					"Wait State"
#define PIXPKEY_NB_OUTPUT_BUFFERS		"Nb Output Buffers"
#define PIXPKEY_OUTPUT_BUFFER				"Output_Buffer_"
#define PIXPKEY_ACQ_CLOCK_MULTIPLY			"Acq Clock Multiply"
#define PIXPKEY_CONFIG_RESET_MODE			"Config Reset Mode"
#define PIXPKEY_DEMAND_MODE					"Demand Mode"


/* Buffer	*/
#define PIXPKEY_BUFFER_WIDTH				"Width"
#define PIXPKEY_BUFFER_HEIGHT				"Height"
#define PIXPKEY_BUFFER_FORMAT				"Format"
#define PIXPKEY_BUFFER_FRAME				"Frame"
#define PIXPKEY_BUFFER_FIELD_ORDER		"Field Order"
#define PIXPKEY_BUFFER_LENGTH				"Length"


/* Pixel	*/
#define PIXPKEY_PIXEL_NB_MEMBERS			"Nb Members"
#define PIXPKEY_PIXEL_MEMBER				"Member_"


/* On-Demand	*/
#define PIXPKEY_ON_DEMAND_NB_COMMANDS	"Nb Commands"
#define PIXPKEY_ON_DEMAND_COMMAND		"Command_"

#endif   // _PIXPKEY_H_
