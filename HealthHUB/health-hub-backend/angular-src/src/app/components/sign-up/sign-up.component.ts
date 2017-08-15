import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { WebsocketService } from '../../services/websocket.service';

import { FlashMessagesService } from 'angular2-flash-messages';

@Component({
  selector: 'app-sign-up',
  templateUrl: './sign-up.component.html',
  styleUrls: ['./sign-up.component.css']
})
export class SignUpComponent implements OnInit {
  connection;
  progress:number = 0;
  user = {
    firstname: 'Karl-Heinz',
    lastname: 'Ruhend',
    technicalAffinity: 'high'
  }
  checkAffinity = true;

  constructor(
      private socketService: WebsocketService,
      private flashMessage: FlashMessagesService,
      private router: Router
  ) { }

  ngOnInit() {

    let that = this;

    that.connection = that.socketService.getMessages().subscribe(message => {
      if (message["type"] == "setup-started") {
        console.log("setup-started");
        that.progress = 1
      }

      if (message["type"] == "setup-scan-2") {
        console.log("setup-scan-2");
        that.progress = 2
      }

      if (message["type"] == "setup-scan-3") {
        console.log("setup-scan-3");
        that.progress = 3
      }

      if (message["type"] == "setup-success") {
        console.log("setup-success");
        that.progress = 4
      }

      if (message["type"] == "registration-success") {
        console.log("registration-success");
        that.progress = -1
        that.flashMessage.show(
          'Hi ' + that.user.firstname + ' your registration was successful!',
          {cssClass: 'alert-success', timeout: 3000 }
        );
      }

      if (message["type"] == "scan-started") {
        this.router.navigate(['/scan-doing']);
      }
    })
  }

  register(){
    this.socketService.sendMessage("setup", "registerUser");
  }

  toggleAffinity(){
    if(this.user.technicalAffinity == 'low'){
      this.user.technicalAffinity = 'high'
      this.checkAffinity = true;
    } else {
      this.user.technicalAffinity = 'low'
      this.checkAffinity = false;
    }
  }

  onSubmit(){
    this.socketService.sendMessage("new-user", this.user);
  }

}
