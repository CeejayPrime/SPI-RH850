# SPI-RH850
This project demonstrates SPI communication protocol by listening to status requests from a master controller, then, the slave device, an arduino, after getting the status message, sends a response message to the master, telling it it's status. We will use the SPI library.

# How to Operate
Before starting, make sure to first select which slave device you will be sending to, then press the start button **ONCE**, automatically, the UI will show all the fault
messages sequentially, then click on the select button to select error message to send. Which ever message is selected will be sent to the corresponding slave device as shown on the UI. After selecting, click on clear button to take it back to the home page.
