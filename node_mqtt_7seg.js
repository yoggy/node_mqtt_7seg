#!/usr/bin/nodejs
//
// node_mqtt_7seg.js - 7segduino control script
//
// settings
//   $ npm install mqtt
//   $ npm install serialport
//   $ npm install confy
//   $ sudo EDITOR=vim ~/node_modules/confy/bin/confy set mqtt_7seg
//
//       {
//         "host": "mqtt.example.com",
//         "port": 1883,
//         "username": "username",
//         "password": "password",
//         "topic": "7seg",
//         "serial": "/dev/ttyUSB0"
//       }
//
//  how to use
//   $ node node_mqtt_7seg.js
//   $ mosquitto_pub -h mqtt.example.com -p 1883 -u username -P password -t 7seg -m 1234
//

var mqtt = require ('mqtt')
var serialport = require('serialport')

var confy = require('confy')
var config;
confy.get('mqtt_7seg', {require:{
	host     : 'mqtt.example.com',
	port     : 1883,
	username : 'username',
	password : 'password',
	topic    : 'topic',
	serial   : '/dev/ttuUSB0'
}}, function(err, result) {
	config = result;
});

var client = mqtt.createClient(config.port, config.host, {
	username: config.username,
	password: config.password
});

var serialPort = new serialport.SerialPort(config.serial, {
	baudRate: 9600,
	dataBits: 8,
	parity: 'none',
	stopBits: 1
});

serialPort.on("open", function () {
	console.log('open : port="' + config.serial);

	client.subscribe(config.topic);
	client.on('message', function(topic, message) {
		console.log('message : topic=' + topic + ', message=' + message);
		serialPort.write(message + "\r\n", function(err, results) {
		});
	});
});

