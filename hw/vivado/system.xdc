set_property  -dict {PACKAGE_PIN  G17  IOSTANDARD LVCMOS33} [get_ports gpio_0_tri_io[0]]      ; ##USB-reset
set_property  -dict {PACKAGE_PIN  U10  IOSTANDARD LVCMOS33} [get_ports gpio_0_tri_io[1]]      ; ## OLED-DC
set_property  -dict {PACKAGE_PIN  U9   IOSTANDARD LVCMOS33} [get_ports gpio_0_tri_io[2]]      ; ## OLED-RES
set_property  -dict {PACKAGE_PIN  AB12 IOSTANDARD LVCMOS33} [get_ports gpio_0_tri_io[3]]      ; ## OLED-SCLK
set_property  -dict {PACKAGE_PIN  AA12 IOSTANDARD LVCMOS33} [get_ports gpio_0_tri_io[4]]      ; ## OLED-SDIN
set_property  -dict {PACKAGE_PIN  U11  IOSTANDARD LVCMOS33} [get_ports gpio_0_tri_io[5]]      ; ## OLED-VBAT
set_property  -dict {PACKAGE_PIN  U12  IOSTANDARD LVCMOS33} [get_ports gpio_0_tri_io[6]]      ; ## OLED-VDD

set_property  -dict {PACKAGE_PIN  T22  IOSTANDARD LVCMOS33} [get_ports gpio_0_tri_io[7]]      ; ##LD0
set_property  -dict {PACKAGE_PIN  T21  IOSTANDARD LVCMOS33} [get_ports gpio_0_tri_io[8]]      ; ##LD1
set_property  -dict {PACKAGE_PIN  U22  IOSTANDARD LVCMOS33} [get_ports gpio_0_tri_io[9]]      ; ##LD2
set_property  -dict {PACKAGE_PIN  U21  IOSTANDARD LVCMOS33} [get_ports gpio_0_tri_io[10]]      ; ##LD3
set_property  -dict {PACKAGE_PIN  V22  IOSTANDARD LVCMOS33}  [get_ports gpio_tri_o[0]]        ;##LD4
set_property  -dict {PACKAGE_PIN  W22  IOSTANDARD LVCMOS33}  [get_ports gpio_tri_o[1]]        ;##LD5
set_property  -dict {PACKAGE_PIN  U19  IOSTANDARD LVCMOS33}  [get_ports gpio_tri_o[2]]        ;##LD6
set_property  -dict {PACKAGE_PIN  U14  IOSTANDARD LVCMOS33}  [get_ports gpio_tri_o[3]]        ;##LD7

set_property  -dict {PACKAGE_PIN  Y11  IOSTANDARD LVCMOS33}  [get_ports gpio_tri_o[6]]        ;##JA1 direction of motor2
set_property  -dict {PACKAGE_PIN  AA11  IOSTANDARD LVCMOS33} [get_ports gpio_tri_o[4]]        ;##JA2 direction of motor0
set_property  -dict {PACKAGE_PIN  Y10  IOSTANDARD LVCMOS33}  [get_ports gpio_tri_o[5]]        ;##JA3 direction of motor1
set_property  -dict {PACKAGE_PIN  AA9  IOSTANDARD LVCMOS33}  [get_ports gpio_tri_o[7]]        ;##JA4 direction of motor3
set_property  -dict {PACKAGE_PIN  AB11  IOSTANDARD LVCMOS33} [get_ports pwm_out[2]]           ;##JA7 motor2 pwm control
set_property  -dict {PACKAGE_PIN  AB10  IOSTANDARD LVCMOS33} [get_ports pwm_out[0]]           ;##JA8 motor0 pwm contorl
set_property  -dict {PACKAGE_PIN  AB9  IOSTANDARD LVCMOS33}  [get_ports pwm_out[1]]           ;##JA9 motor1 pwm control
set_property  -dict {PACKAGE_PIN  AA8  IOSTANDARD LVCMOS33}  [get_ports pwm_out[3]]           ;##JA10 motor3 pwm control