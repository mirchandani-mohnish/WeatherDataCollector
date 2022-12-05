const {SerialPort} = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');
const axios = require("axios");

const port = new SerialPort({path: 'COM9', baudRate: 9600 });
const parser = port.pipe(new ReadlineParser());


// const postDataRepeat = setTimeout(postData, 1000);

// const postData = () => {

port.on("open", () => {
  console.log('serial port open');
});

parser.on('data', async (receivedData) =>{
  console.log(receivedData);
  // axios({
  //   method: 'post',
  //   url: 'http://localhost:3000/data',
  //   body: receivedData
  // })
  
  axios.post("http://localhost:3000/data", {receivedData: JSON.stringify(receivedData)}).then((response) => console.log("posted weather data")).catch((e) => console.log(e));
});

// }