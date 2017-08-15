import { Component, OnInit } from '@angular/core';
import { Router, NavigationEnd } from '@angular/router';
import { Location } from '@angular/common';

import { UserService } from '../../services/user.service';
import { User } from '../../models/user.model'

import { AppComponent } from '../../app.component';

@Component({
  selector: 'app-navbar',
  templateUrl: './navbar.component.html',
  styleUrls: ['./navbar.component.css']
})
export class NavbarComponent implements OnInit {
  user: User;
  showArrow = false;
  technicalAffinity: string;
  subscription;
  body = document.getElementsByTagName('body')[0];

  constructor(
    private userService: UserService,
    private router: Router,
    private location: Location,
    private rootComp: AppComponent
  ) {
      let that = this;

      //subscribe to user-changes
      that.subscription = that.userService.subscribe(function(){
        that.user = that.userService.getUser();
      });

      //observe the currently active page. If it is history-page show "back"-arrow
      router.events.subscribe((event:any) => {
        if(event instanceof NavigationEnd){
          if(event.urlAfterRedirects.includes('scan-doing') || event.urlAfterRedirects.includes('scan-start') || event.urlAfterRedirects.valueOf() == '/'){
            that.rootComp.cssClass = 'white';
            that.showArrow = false;
          } else {
            that.rootComp.cssClass = '';
            that.showArrow = true;
          }
        }
      });
  }

  ngOnInit() {
    this.user = this.userService.getUser();
  }

  back(){
    this.location.back();
  }

  logout(){
    this.userService.logout();
    this.userService.emit();
  }

  ngOnDestroy() {
    this.subscription.unsubscribe();
  }

}
