# mist-stm32

++ fpga config (JTAG)
   boot board through JTAG

++ PS/2 keyboard 

++ CDC interface

+- OSD

++ boot ZX and ESXDOS 

-- sound

-- PS/2 mouse

Notes:

Additional HW plugs via STM32CubeMX (not inside Keil uVision).
STCubeGenerated.ioc:
.\mist-stm32\mist_stm32\RTE\Device\STM32F407VETx\STCubeGenerated\STCubeGenerated.ioc

SPECTRUM.ROM is ESXMMC.BIN of esxdos085.zip (http://esxdos.org/)

Changes in spectrum-ep4ce22.rar :
 - pinout changed for my EP4CE22F17 dev.board 
 - 50MHz clock on board
 - appended cmd code indication on one digit 7segment indicator for data_io commands
 - changed VGA output for 3 bit lines on my fpga board.

VGA_color_block.rar - VGA test (changed example of my board)
data_io.rar - modelsim model 