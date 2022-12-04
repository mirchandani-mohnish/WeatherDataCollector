const {SerialPort} = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');


const port = new SerialPort({path: 'COM9', baudRate: 9600 });
const parser = port.pipe(new ReadlineParser({ delimiter: '//' }));

// Read the port data
port.on("open", () => {
  console.log('serial port open');
});

parser.on('data', data =>{
  console.log('got word from arduino:', data);
});