Arduino UNO Regulates Air Conditioner

Why do this? The AC temperature is controlled by an economy Honeywell assembly. It has a metal disk which expands or contracts with temperature. It presses the button on a microswitch which powers the AC. This device is slow to turn on and then it runs for too long creating a 4 degree room temperature variance.

The Arduino has a prototyping board (shield) with a LM35 temperature sensor connected to input A1. A potentiometer is connected to A0 to provide a reference voltage of about 0.23v. The Arduino program turns a relay on or off when the LM35 sensor varies from the reference voltage. It limits the room temperature variance to less than 1 degree.
