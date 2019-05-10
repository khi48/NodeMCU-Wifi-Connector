# NodeMCU_wifiConnect
Connect to NodeMCU over wifi then pass through router ssid and password

Firstly, connect an LED to pin D0 of the NodeMCU in series with a 2.2kohm resistor to ground.
Next, pair your device (phone/laptop) to the NodeMCU local WiFi network "" using the password "".
Once connected, enter the following commands into the browers to interact with the NodeMCU:

Commands: 
http://192.168.4.1/led/off                          - Turns the LED at pin D0 off
http://192.168.4.1/led/on                           - Turns the LED at pin D0 on
http://192.168.4.1/ssid/{your WiFi name}            - Passes the ssid of your WiFi network to the NodeMCU
http://192.168.4.1/password/{your WiFi password}    - Passes the password of your WiFi network to the NodeMCU

One the NodeMCU has recieved both the WiFi ssid and password, it will connect to the network. As there is nothing
in the loop currently, the LED will only flash. 
