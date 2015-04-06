# ARDUINO Servo Code (Methods explained)

###String getValue
#####Definition
######Method to split string by a given character
#####Syntax
######getValue(string, separator_character, index)

###Setup
#####Definition
######Main Arduino Function

###receiveEvent
#####Definition
######Method called when message in received through Wire transmission

###constructWireString
#####Definition
######Take each character received through Wire transmission, construc string until $ character is received and then call wireAction and reset receiverWireString String

###wireAction
#####Definition
######Split Wire received string by ';' character and create new strings to execute read/write servo action.




