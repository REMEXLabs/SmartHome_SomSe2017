import { Component, OnInit } from '@angular/core';

import { UserService } from '../../services/user.service';

@Component({
  selector: 'app-settings',
  templateUrl: './settings.component.html',
  styleUrls: ['./settings.component.css']
})
export class SettingsComponent implements OnInit {
  //technicalAffinity
  technicalAffinity: string;
  checkAffinity: boolean;

  //thirdPartyAccess
  thirdPartyAccess: boolean;
  checkAccess: boolean;

  constructor(
    private userService: UserService
  ) {
    this.technicalAffinity = this.userService.getUserTechnicalAffinity();
    this.thirdPartyAccess = this.userService.getThirdPartyAccess();

    this.checkAffinity = (this.technicalAffinity == 'high' ? true : false);
    this.checkAccess = (this.thirdPartyAccess == true ? true : false);
  }

  ngOnInit() {
  }

  toggleAffinity(){
    if(this.technicalAffinity == 'high'){
      this.userService.setUserTechnicalAffinity('low');
      this.checkAffinity = false;
    } else {
      this.userService.setUserTechnicalAffinity('high');
      this.checkAffinity = true;
    }
    this.userService.emit();
    this.technicalAffinity = this.userService.getUserTechnicalAffinity();
  }

  toggleThirdPartyAccess(){
    if(this.thirdPartyAccess == true){
      this.userService.setThirdPartyAccess(false);
      this.checkAccess = false;
    } else {
      this.userService.setThirdPartyAccess(true);
      this.checkAccess = true;
    }
    this.userService.emit();
    this.thirdPartyAccess = this.userService.getThirdPartyAccess();
  }

}
