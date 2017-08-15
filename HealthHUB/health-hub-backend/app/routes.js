var serial = require('./serial.js'),
express = require('express'),  //web server
app = express(),
server = require('http').createServer(app);
db = require('./database.js');

app.use(function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  next();
});

app.get('/recent-user', function (req, res) {
  db.getLastScan(function(scan) {
    var data = {
      lastname: scan._user.lastname,
      firstname: scan._user.firstname,
      thirdPartyAccess: scan._user.thirdPartyAccess,
      scandate: scan.date,
      pulse: scan.pulse,
      temp: scan.temp_formatted,
      stress: "normal"
    };
    res.send(data)
  });
})

app.post('/setup', function (req, res) {

  var buf = new Buffer("HHMESSAGESETUPID3\n", "utf-8");
  serial.port.write(buf, function (error) {
      if (error) {
          res.send(error);
      } else {
          res.send("Success");
      }
  });
})

app.listen(3000, function () {
  console.log('Example app listening on port 3000!')
})

app.use(express.static('public')); //tell the server that ./public/ contains the static webpages

module.exports.server = server;
