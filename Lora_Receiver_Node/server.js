const express = require('express');
const mongoose = require('mongoose');
const weather = require('./models/weather');
const bodyParser = require('body-parser');
const app = express();
app.set('view engine', 'ejs');

app.use(bodyParser.json()); // for parsing application/json
app.use(bodyParser.urlencoded({ extended: true })); // for parsing application/x-www-form-urlencoded

app.use(bodyParser.json()); // for parsing application/json
app.use(bodyParser.urlencoded({ extended: true })); // for parsing application/x-www-form-urlencoded

app.get('/', async (req, res) => {
  let weatherData;
  await weather.find({}).then((res) => {
    console.log(res);
    weatherData = res;
  });
  res.render('home.ejs', { weatherData: weatherData });
});
app.get('/w', async (req, res) => {
  let weatherData;
  await weather.find({}).then((res) => {
    // console.log(res);
    weatherData = res;
  });
  res.send({ weatherData: weatherData });
});
app.post('/data', (req, res) => {
  const weatherData = req.body;
  console.log(weatherData);
  const weatherDataArray = weatherData.receivedData.split('//');
  weatherDataArray.forEach((element) => {
    console.log(element);
    console.log(+element);
  });
  const newWeatherPacket = new weather({
    temperature: +weatherDataArray[1],
    humidity: +weatherDataArray[2],
    pressure: +weatherDataArray[3],
    altitude: +weatherDataArray[4],
    aqi: +weatherDataArray[5],
  });

  newWeatherPacket.save((e) => {
    console.log(e);
  });
  res.send('success');
  // weather.save(weatherData)
});

app.post('/data', (req, res) => {
  const weatherData = req.body;
  console.log(weatherData);
  const weatherDataArray = weatherData.receivedData.split('//');
  weatherDataArray.forEach((element) => {
    console.log(element);
    console.log(+element);
  });
  const newWeatherPacket = new weather({
    temperature: +weatherDataArray[1],
    humidity: +weatherDataArray[2],
    pressure: +weatherDataArray[3],
    altitude: +weatherDataArray[4],
    aqi: +weatherDataArray[5],
  });

  newWeatherPacket.save((e) => {
    console.log(e);
  });
  res.send('success');
  // weather.save(weatherData)
});

mongoose.connect(
  'mongodb+srv://admin:admin@cluster0.vkoedeg.mongodb.net/?retryWrites=true&w=majority',
  {
    useNewUrlParser: true,
    useFindAndModify: false,
    useUnifiedTopology: true,
  }
);

const db = mongoose.connection;
db.on('error', console.error.bind(console, 'connection error: '));
db.once('open', function () {
  console.log('Connected successfully');
});

app.listen(3000, () => {
  console.log('Server is running at port 3000');
});
