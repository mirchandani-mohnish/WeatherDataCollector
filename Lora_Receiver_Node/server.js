const express = require("express");
const mongoose = require("mongoose");


const app = express();
app.set('view engine', 'ejs');


app.get("/", (req, res) => {
    res.render("home.ejs")
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