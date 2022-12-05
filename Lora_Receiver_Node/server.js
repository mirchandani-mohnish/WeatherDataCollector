const express = require("express");
const mongoose = require("mongoose");
const weather = require("./models/weather");
const bodyParser = require("body-parser");
const app = express();
app.set('view engine', 'ejs');


app.use(bodyParser.json()) // for parsing application/json
app.use(bodyParser.urlencoded({ extended: true })) // for parsing application/x-www-form-urlencoded

app.get("/", (req, res) => {
    weather.find({}).then((res) => {console.log(res);})
    res.render("home.ejs")
})


app.post("/data", (req,res) => { 
    const weatherData = req;
    console.log(req.body);
    res.send("success");
    // weather.save(weatherData)
})





mongoose.connect('mongodb+srv://admin:admin@cluster0.vkoedeg.mongodb.net/?retryWrites=true&w=majority',
  {
    useNewUrlParser: true,
    useFindAndModify: false,
    useUnifiedTopology: true,
  }
);


const db = mongoose.connection;
db.on("error", console.error.bind(console, "connection error: "));
db.once("open", function () {
  console.log("Connected successfully");
});




app.listen(3000, () => {
    console.log("Server is running at port 3000");
  });