G90 ; absolute positioning
G21 ; units in mm
F100 ; default feed rate

G38.2 Z-5 F50 ; probe down 5mm
G0 Z5        ; retract after probing
M2           ; program end
