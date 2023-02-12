# ProMicro Breakout + RGB

![ProMicro Breakout + RGB Board Image](../Preview-Images/ProMicro-Breakout%20%2B%20RGB.png)

## Description

This board is just for the bare essentials, providing 12 buttons (WITHOUT lights), 2 quadrature encoder inputs, and 1 ARGB header.

## Bill of Materials

| Part | Description | Qty | Link |
|:---|:---|:---:|:---|
| Arduino Pro Micro | Microprocessor | 1 | Search "Pro Micro" on Aliexpress, ensure the listing says 32U4 |
| JST XH 2P Header | Connector for buttons and power (optional) | 12 (+ 1 optional) | https://www.lcsc.com/product-detail/Wire-To-Board-Wire-To-Wire-Connector_BOOMELE-Boom-Precision-Elec-XH-2A_C20079.html |
| JST XH 4P Header | Connector for encoder and RGB | 3 | https://www.lcsc.com/product-detail/Wire-To-Board-Wire-To-Wire-Connector_BOOMELE-Boom-Precision-Elec-XH-4A_C37815.html |

Connectors can also be found on Aliexpress by searching "JST XH".

## Configuration

### Power Selection

Typically, you will be using USB power for this board. Solder the middle and right pads together on jumper JP1.

By soldering the other two pads, the LEDs will be powered via the JST XH 2P connector. This can allow you to use 12V leds, if this is desired.