const mongoose = require("mongoose");
  const { Schema } = mongoose;

  const weatherSchema = new Schema({
    date: {type: Date}, // String is shorthand for {type: String}
    temperature: Number,
    pressure:   Number,
    humidity: Number,
    altitude: Number,
    wind_speed: {default: 0},
    aqi: Number
  });



  module.exports = weather = mongoose.model("weatherpacket", weatherSchema,"weatherCollection");