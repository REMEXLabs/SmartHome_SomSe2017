var mongoose = require('mongoose');

var userSchema = mongoose.Schema({
  lastname: String,
  firstname: String,
  birthdate: Date,
  technicalAffinity: {type: String, default: "high"},
  thirdPartyAccess: {type: Boolean, default: true},
  fingerprint_id: Number
});

userSchema.virtual('age').get(function () {
  var today = new Date();
  var birthDate = this.birthdate;
  var age = today.getFullYear() - birthDate.getFullYear();
  var m = today.getMonth() - birthDate.getMonth();
  if (m < 0 || (m === 0 && today.getDate() < birthDate.getDate())) {
    age--;
  }
  return age;
});

userSchema.methods.add = function(lastname, firstname, birthdate, technicalAffinity, fingerprint_id, callback){
  this.lastname = lastname;
  this.firstname = firstname;
  this.birthdate = birthdate;
  this.fingerprint_id = fingerprint_id;
  this.technicalAffinity = technicalAffinity;
  return this.save(callback);
}

module.exports = mongoose.model('User', userSchema);
