# SSC-32-Servo-Controller-C-Library
==================
This Library will allow you to write C programs to interface with the SSC-32 Servo Controller sold by Lynxmotion.
<hr />
This is a very bare-bone library and could use a lot of developement.
<b>Areas of Improvement:</b>
<ul>
<li>Ability to run motors concurrently rather than one at a time</li>
<li>Ability to use on more platforms rather than linux</li>
</ul>

<b>How to setup</b>
<ol>
<li>Place files in a directory that can use the gcc/g++ compiler</li>
<li>You will need to specify what port the servo is connected to on the computer. I used a usb to rs-232 connector to interface with the controller, so I specified it as a usb port. You will need to edit the code in servo.c and change the value of the <code>PORT[13]</code> variable to something you can use.</li>
<li>Change the <code>BAUD[6]</code> accordingly as well, default is 115200</li>
<li>servoInteract.c will be the file that we use to make sure our servos run. Use it as a guide for when you build your own program.</li>
<li>Now you can run the makefile. Don't worry about the radio.* files (I will remove those in the next update, get rid of them if you want). There are a few build specifications that aren't utilized, and will be fixed soon.</li>
<li>Run: <code>make servoInteract</code></li>
<li>You will have a resulting executable file called servoInteract. You can run the executable by: <code>./servoInteract</code></li>
</ol>
