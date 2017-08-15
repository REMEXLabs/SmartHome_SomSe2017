var serialPort = require('serialport');
db = require('./database.js');
socket = require('./socket.js');

var typeStructure = ["message"];
var streamStructure = ["message", "sensor", "signal"];
var errorStructure = ["message", "sensor"];
var stateStructure = ["message", "value"];
var dataStructure = ["message", "id", "heartrate", "temp", "gsr"];

// routes
var port = new serialPort("/dev/ttyACM0", {
  baudrate: 9600,
  parser: serialPort.parsers.readline('\n')
});

port.on('open', function() {
  port.write('main screen turn on', function(err) {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('message written');
  });
});

port.on('data', function (data) {

    console.log("raw: " + data);

    var input = {};

    if (data !== undefined) {
      var type = parse(data, typeStructure);

      if (type.message === "DATA"){
        input = parse(data, dataStructure);
      } else if (type.message === "STREAM"){
        input = parse(data, streamStructure);
      } else if (type.message === "ERROR"){
        input = parse(data, errorStructure);
      } else if (type.message === "SCANSTATE" || type.message === "SETUPSTATE"){
        input = parse(data, stateStructure);
      }

      console.log(JSON.stringify(input));
    }

    // scan started
    if (input.message == "SCANSTATE" && input.value == "1") {
      socket.io.sockets.emit('message', {type:'scan-started'});
    }

     // setup
    if (input.message == "SETUPSTATE" && input.value == "1") {
      socket.io.sockets.emit('message', {type:'setup-started'});
    }

    if (input.message == "SETUPSTATE" && input.value == "11") {
      socket.io.sockets.emit('message', {type:'setup-scan-1'});
      console.log("SETUPSTATE 11");
    }

    if (input.message == "SETUPSTATE" && input.value == "12") {
      socket.io.sockets.emit('message', {type:'setup-scan-2'});
      console.log("SETUPSTATE 12");
    }

    if (input.message == "SETUPSTATE" && input.value == "13") {
      socket.io.sockets.emit('message', {type:'setup-scan-3'});
      console.log("SETUPSTATE 13");
    }

    if (input.message == "SETUPSTATE" && input.value == "18") {
      socket.io.sockets.emit('message', {type:'setup-success'});
      console.log("SETUPSTATE 18");
    }

    // user identified
    if (input.message == "DATA"
      && input.hasOwnProperty("id")
      && !input.hasOwnProperty("heartrate")
      && !input.hasOwnProperty("temp")
      && !input.hasOwnProperty("gsr")
      && (0 < input.id)
      && (input.id < 7)){
        db.getUser(input.id, function(user) {
          if (user !== null) {
            var data = {
              id: user._id,
              lastname: user.lastname,
              firstname: user.firstname,
              technicalAffinity: user.technicalAffinity,
              thirdPartyAccess: user.thirdPartyAccess
            }
            socket.io.sockets.emit('message', {type:'user-identified', user:JSON.stringify(data)});
          }
      });
    }

    // scan finished
    else if (input.message == "DATA"
      && input.hasOwnProperty("id")
      && input.hasOwnProperty("heartrate")
      && input.hasOwnProperty("temp")
      && input.hasOwnProperty("gsr")){
        console.log("scan finished");
        socket.io.sockets.emit('message', {type:'scan-finished'});
        if (0 < input.id && input.id < 7) {
          db.addScan(input.id, input.gsr, input.heartrate, input.temp, function(scan){
            console.log("scan saved");
          });
        }
    }

    // gsr finished
    else if (input.message == "DATA"
      && !input.hasOwnProperty("id")
      && input.hasOwnProperty("gsr")){
        var sensor = {
          gsr : {
            value: input.gsr,
            text: "normal"
          }
        }
        socket.io.sockets.emit('message', {type:'sensor-finished', data: sensor});
    }

    // pulse finished
    else if (input.message == "DATA"
      && !input.hasOwnProperty("id")
      && input.hasOwnProperty("heartrate")){
        var sensor = {
          pulse : {
            value: input.heartrate,
            text: "low"
          }
        }
        socket.io.sockets.emit('message', {type:'sensor-finished', data: sensor});
    }

    // temp finished
    else if (input.message == "DATA"
      && !input.hasOwnProperty("id")
      && input.hasOwnProperty("temp")){
        var temp = input.temp;
        var tempStr=temp.substring(0,temp.length-2)+"."+temp.substring(temp.length-2);
        var sensor = {
          temp : {
            value: tempStr,
            text: "low"
          }
        }
        socket.io.sockets.emit('message', {type:'sensor-finished', data: sensor});
    }

    // pulse stream
    else if (input.message == "STREAM"){
      socket.io.sockets.emit('message', {type:'pulse-stream', value: input.signal});
    }

    // scan failed
    else if (input.message == "STATE" && input.value == "3") {
      socket.io.sockets.emit('message', {type:'scan-failed'});
    }

});

exports.setupFingerprint = function() {
  console.log("hihi");

  var buf = new Buffer("HHMESSAGESETUPID4\n", "utf-8");
  port.write(buf, function (error) {
      if (error) {
          console.log(error);
      } else {
          // success
      }
  });
};

port.on('error', function(err) {
  console.log('Error: ', err.message);
});

module.exports.port = port;

function parse(data, type){

  var structure = type;
  var result = {};
  var indexes = getIndexes(data);
  var nextIndex = -1;

  if (indexes.start != -1) {
    data = data.substring(indexes.start, data.length);
    delete indexes["start"];
  } else {
    return result;
  }

  result.raw = data;

  structure.forEach(function(element, index, array){
    nextIndex = getNextIndex(element, indexes);
    if (indexes[element] != -1 && nextIndex != -1){
      result[element] = data.substring(indexes[element] + element.length, nextIndex);
      delete indexes[element];
    }
  });

  return result;
}

function getNextIndex(keyword, array){
  var nextIndex = -1;

  for (var key in array){
      if (key != keyword && array[key] != -1){
          nextIndex = array[key];
          break;
      }
    }

  return nextIndex;
}

function getIndexes(data){
  var index = {};

  index.start = data.indexOf("HH");
  index.message = data.indexOf("MESSAGE");
  index.value = data.indexOf("VALUE");
  index.id = data.indexOf("ID");
  index.heartrate = data.indexOf("HEARTRATE");
  index.temp = data.indexOf("TEMP");
  index.gsr = data.indexOf("GSR");
  index.sensor = data.indexOf("SENSOR");
  index.signal = data.indexOf("SIGNAL");
  index.end = data.indexOf("\r");

  return index;
}
