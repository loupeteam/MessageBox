# Info
Library is provided by Loupe  
https://loupe.team  
info@loupe.team  
1-800-240-7042  

# Description
The MessageBox library is used to create event based popups in webHMI applications. The popup has a prompt, an optional user input, and buttons. This library has two structures; one for creating a new message and one for interacting with the currently active popup.

Messages can be added with normal priority (added to the bottom of the queue) or high priority (added to the top). Messages can be removed based on a messageId that is returned when the message is created.

Modals from the Bootstrap library are required in order to see the pop-up on the HMI. Please see the Html section for example code.

# Use Cases
MessageBox is used in, but is not limited to the following cases:

-Machine operator confirmation popups  
-Jog motor confirmation  
-Alert popups  
-Disconnection notifications  
-Error alerts  
-Low fluid levels  
-Missing modules  
-Machine ready  
-Security and Access  
-Scenarios that require user input  
-Spindle speed  

For more documentation and examples, see https://loupeteam.github.io/LoupeDocs/libraries/messagebox.html

# Installation
To install using the Loupe Package Manager (LPM), in an initialized Automation Studio project directory run `lpm install messagebox`. For more information about LPM, see https://loupeteam.github.io/LoupeDocs/tools/lpm.html

## Licensing

This project is licensed under the [MIT License](LICENSE).