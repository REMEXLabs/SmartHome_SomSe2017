var User = require('./models/user.js');
var Scan = require('./models/scan.js');

var mongoose = require('mongoose');
mongoose.Promise = global.Promise;

mongoose.connect('mongodb://127.0.0.1/data/db');
var db = mongoose.connection;

db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function() {
  console.log("db connected!");

  // var newUser = new User();
  // newUser.add("Walz", "Mario", "1966-12-12", "low", 1, function(response){
  // console.log("Saved new user");
  // });
  // var newUser2 = new User();
  // newUser2.add("Bochan", "David", "1966-12-12", "low", 3, function(response){
  // console.log("Saved new user");
  // });
  // var newUser3 = new User();
  // newUser3.add("Schmidt", "Eric", "1966-12-12", "high", 5, function(response){
  // console.log("Saved new user");
  // });

  // exports.getAllUsers(function(){});
  // exports.addScan(1, "60", "70", "60", function(){});
  // exports.getAllScans(function(){});
  // exports.removeAllScans();
  // exports.removeAllUsers();
  // exports.getScanHistory("59468fdd87b035a211267043",5);

});

exports.getAllUsers = function(callback) {
  User.find(function (err, users) {
    if (err) return console.error(err);
    console.log(users);
    callback(users)
  });
}

exports.getUser = function(fingerprint_id, callback) {
  User.findOne({'fingerprint_id' : fingerprint_id}, function (err, user) {
    if (err) return console.error(err);
    console.log(user);
    callback(user)
  });
}

exports.getAllScans = function(callback) {
  Scan.find().
  populate('_user').
  exec(function (err, scans) {
    if (err) return console.error(err);
    console.log(scans);
    callback(scans)
  });
}

exports.getLastScan = function(callback) {
  Scan.findOne().
  populate('_user').
  sort({date: -1}).
  limit(1).
  exec(function (err, scan) {
    if (err) return console.error(err);
    callback(scan);
  });
};

exports.getScanHistory = function(userId, number, callback) {
  Scan.find({_user: userId}).
  limit(number).
  sort({date: -1}).
  exec(function (err, scans) {
    if (err) return console.error(err);
    console.log(scans);
    callback(scans);
  });
}

exports.addScan = function(fingerprint_id, gsr, pulse, temp, callback) {
  User.findOne({'fingerprint_id' : fingerprint_id}, function (err, user) {
    if (err) return console.error(err);
    if ((user !== undefined) && (user !== null)) {
      var newScan = new Scan();
      newScan.add(user._id, gsr, pulse, temp, function(err, scan){
        console.log("Saved scan");
        console.log(scan);
        callback(scan);
      });
    }
  });
}

exports.addUser = function(lastname, firstname, technicalAffinity, callback) {
  var newUser = new User();
  newUser.add(lastname, firstname, "1986-12-12", technicalAffinity, 4, function(err, user){
    console.log("Saved user");
    console.log(user);
    callback(user);
  });
}

exports.removeAllScans = function(callback) {
  Scan.remove({}, function (err) {
    if (err) return console.error(err);
    console.log("All scans removed");
    callback();
  });
}

exports.removeAllUsers = function(callback) {
  User.remove({}, function (err) {
    if (err) return console.error(err);
    console.log("All users removed");
    callback();
  });
}
