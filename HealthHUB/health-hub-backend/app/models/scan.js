var mongoose = require('mongoose');

var scanSchema = mongoose.Schema({
  _user: {type: mongoose.Schema.Types.ObjectId, ref: 'User'},
  date: {type: Date, default: Date.now},
  gsr: Number,
  pulse: Number,
  temp: Number,
});

scanSchema.virtual('gsr_level').get(function () {
  var gsr = this.gsr
  if (gsr < 40) {
    return "low";
  }
  else if (gsr >= 40 && gsr < 60) {
    return "normal";
  }
  else if (gsr >= 60) {
    return "high";
  }
});

scanSchema.virtual('temp_level').get(function () {
  var temp = this.temp
  if (temp < 36) {
    return "low";
  }
  else if (temp >= 36 && temp < 37) {
    return "normal";
  }
  else if (temp >= 37 && temp < 38) {
    return "high";
  }
  else if (temp >= 38) {
    return "very high";
  }
});

scanSchema.virtual('temp_formatted').get(function () {
  var temp = this.temp.toString();
  var tempStr=temp.substring(0,temp.length-2)+"."+temp.substring(temp.length-2);
  return tempStr;
});

scanSchema.virtual('pulse_level').get(function () {
  var pulse = this.pulse;
  var age = this._user.age;
  if (age > 15 && age < 60) {
    if (pulse < 60) {
      return "low";
    }
    else if (pulse >= 60 && pulse < 80) {
      return "normal";
    }
    else if (pulse > 80) {
      return "high";
    }
  }
  else if (age > 60) {
    if (pulse < 80) {
      return "low";
    }
    else if (pulse >= 80 && pulse < 85) {
      return "normal";
    }
    else if (pulse > 85) {
      return "high";
    }
  }
});

scanSchema.methods.add = function(user, gsr, pulse, temp, callback){
    this._user = user;
    this.gsr = gsr;
    this.pulse = pulse;
    this.temp = temp;
    return this.save(callback);
}

module.exports = mongoose.model('Scan', scanSchema);
