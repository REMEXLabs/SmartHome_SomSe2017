
import { Injectable, EventEmitter } from '@angular/core';
import { Http } from '@angular/http';

import { User } from '../models/user.model';

@Injectable()
export class UserService {
  user:User;

  userChange: EventEmitter<object> = new EventEmitter();

  constructor(
    private http: Http
  ) {
    this.user = new User()
  }

  //Emit user-change to subscribers
  emit() {
   this.userChange.emit();
  }

  //Subscribe to changes to user-object
  subscribe(callback) {
    return this.userChange.subscribe(data => {callback(data)});
  }

  logout(){
    this.user = new User();
  }

  //set currently active user
  setUser(user){
    this.user = JSON.parse(user);
  }

  // get current user
  getUser(){
      return this.user;
  }

  // set users' technical affinity
  setUserTechnicalAffinity(affinity:string){
    this.user.technicalAffinity = affinity;
  }

  //get users' technical affinity
  getUserTechnicalAffinity(){
    return this.user.technicalAffinity;

  }

  setThirdPartyAccess(set: boolean){
    this.user.thirdPartyAccess = set;
  }

  getThirdPartyAccess(){
    return this.user.thirdPartyAccess;
  }

}
