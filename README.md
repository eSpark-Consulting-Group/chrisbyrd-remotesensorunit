# chrisbyrd-remotesensorunit
To design schematic and PCB of remote sensor unit.

# Requirements

- ESP32-S3R8 SOC with 8MB flash
- PCB trace WiFi antenna
- 1x tall MPCIE slot to accommodate our existing comms module cards (including our full pinout)
- Powered by USB with rechargeable LiIon/LiPo battery (solder bridge to support JTAG on USB connector)
- If POE is present, can this also charge the battery?
- GPIO pin to monitor battery charge
- ATECC608a
- Onboard air temperature & humidity sensor (either combined or two separate components). Client needs two options, the one currently present on board and then another BME680, only one of the two sensors will be used at one time and the other will be DNP (decided by client)
- Onboard piezo sounder
- 8x external sensor probe sockets, each connected by RJ11. It will be a mixture of digital and analogue sensors so will need GPIO capable of ADC.
- Side reset button
- 2 output relays (no/nc/c)
- OLED display and 3 buttons (ideally re-use our existing OLED+BTN board). The OLED advanced board will be used in this design so ensure all the connections are set accordingly.
- Small footprint as possible

Example Sensor Probes we will use (with our own RJ11 pinout)

- Temperature probe: DS18B20 digital temperature sensor (waterproof version).
- Optical Pulse (digital) https://github.com/openenergymonitor/optical-pulse-sensor (with RJ11 instead of RJ45)
- 1v Analogue CT electrical current sensor: https://en.yhdc.com/comp/file/download.do?id=950
