# CAN Jammer

### About CAN Jammer
The CAN Jammer Firmware works on a dual CAN bus device like the USBCAN-2A. It acts as a CAN 2.0B gateway that goes in between a node of interest (Target) and the rest of the nodes in the network. 
What the CAN Jammer can do:<br>
* It displays which side the CAN messages are coming from, CAN1 or CAN2.
  * It can block certain CAN ID's from passing through.
* Or you can block all CAN ID's except for the ID's that you do want to pass through.
* You can mask which bits of certain bytes that you want to either toggle, set high or set low.
* You can override certain bytes with hardcoded bytes.
* You can send CAN messages to either CAN1 or CAN2 side, isolated from the opposite side.

<img width="800" height="476" alt="Image" src="https://github.com/user-attachments/assets/4630f861-c643-40c4-b6f8-72c802f6ca54" />

More information can be found on the Wiki https://github.com/karlyamashita/CAN_Jammer_STM32F105RB/wiki



