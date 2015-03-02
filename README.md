node_mqtt_7seg.js
====
7segduino control script. You can control 7segduino using mqtt message.

* 7segduino
  * http://morecatlab.akiba.coocan.jp/lab/index.php/aruino/7segduino/

7segduino settings
----
Please be sure that you uploaded serial_7seg.ino to 7segduino.

Script settings
----

    $ npm install mqtt
    $ npm install serialport
    $ npm install confy
    $ sudo EDITOR=vim ~/node_modules/confy/bin/confy set mqtt_7seg
   
        {
          "host": "mqtt.example.com",
          "port": 1883,
          "username": "username",
          "password": "password",
          "topic": "topic_for_7seg",
          "serial": "/dev/ttyUSB0"
        }

How to use
----
Run node_mqtt_7seg.js

    $ node node_mqtt_7seg.js
    open : port="/dev/ttyUSB0
        .
        .
        .

Publish 4-digit number to be displayed on the 7segduino.

    $ mosquitto_pub -h mqtt.example.com -p 1883 -u username -P password -t topic_for_7seg -m 1234

