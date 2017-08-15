import { Component, OnInit, HostBinding } from '@angular/core';

import { UserService } from './services/user.service';

@Component({
  selector: 'body',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
  title = 'app works!';
  userLevel: string;
  subscription;

  constructor(
    private userService: UserService
  ){
    let that = this;
    that.subscription = that.userService.subscribe(function(){
      that.userLevel = that.userService.getUserTechnicalAffinity();
    });

  }

  ngOnInit(){
    this.userLevel = this.userService.getUserTechnicalAffinity();
  }

  @HostBinding('class') public cssClass = 'white';

}
