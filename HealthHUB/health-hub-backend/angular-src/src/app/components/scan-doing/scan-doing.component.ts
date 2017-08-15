import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { FlashMessagesService } from 'angular2-flash-messages';

import { HealthValues } from '../../models/user-health-values.model';
import { User } from '../../models/user.model';

import { UserService } from '../../services/user.service';
import { HealthValueService } from '../../services/health-value.service';
import { WebsocketService } from '../../services/websocket.service';

import { SerializationHelper } from '../../helpers/serialization.helper';

declare var Chart:any;

@Component({
  selector: 'app-scan-doing',
  templateUrl: './scan-doing.component.html',
  styleUrls: ['./scan-doing.component.css']
})
export class ScanDoingComponent implements OnInit  {
  connection;
  message;
  scanning: boolean = true;
  scanSuccessful: boolean = false;

  user: User;
  healthValues:HealthValues = new HealthValues();

  stressChartOptions:any = {
    scaleShowVerticalLines: false,
    responsive: false,
    scales: {
      yAxes: [{
       ticks: {
         stepSize: 5
       },
       display: false,
       scaleLabel: {
         display: false
       }
     }],
      xAxes: [{
        display: false
      }]
    },
    legend: false,
    elements: { point: { radius: 0 } },
    //animation : false
    animation: {
      duration: 10
    }
  };

  stressData = [
    {data: [
      512, 530, 512, 499, 512, 512, 512, 512, 510, 512,
      512, 530, 512, 499, 512, 512, 512, 512, 510, 512,
      512, 530, 512, 499, 512, 512, 512, 512, 510, 512
    ], fill: false}
  ];

  dateLabels:number[] = [
    1,2,3,4,5,6,7,8,9,10,
    1,2,3,4,5,6,7,8,9,10,
    1,2,3,4,5,6,7,8,9,10
  ];

  /* begin mock */
  counter = 0;

  /* end mock */

  constructor(
    private socketService: WebsocketService,
    private userService: UserService,
    private healthService: HealthValueService,
    private flashMessage: FlashMessagesService,
    private router: Router
  ) {}

  ngOnInit() {
    let that = this;
    that.user = that.userService.getUser();
    that.healthValues = that.healthService.getHealthValues();

    // setTimeout(
    //   function(){
    //     SerializationHelper.toInstance(that.healthValues, that.dummyHealthValues);
    //   }, 4000);
    //
    // setTimeout(
    //   function(){
    //     SerializationHelper.toInstance(that.healthValues, that.dummyHealthValues2);
    //   }, 5000);
    //
    // setTimeout(
    //   function(){
    //     SerializationHelper.toInstance(that.healthValues, that.dummyHealthValues3);
    //   }, 7000);

    //pulse wave
    setInterval(function(){
      var values = [512, 530, 512, 499, 512, 512, 512, 512, 510, 512]

      if(that.counter == 9){
        that.shiftPulseWave(values[that.counter])
        that.counter = 0;
      } else {
        that.shiftPulseWave(values[that.counter])
        that.counter = that.counter+1
      }

    },180)

    /* end mock */

    //Communication with WebSocket
    that.connection = that.socketService.getMessages().subscribe(message => {

      if (message["type"] == "scan-started") {
        console.log("scan-started");
        // reset healthValues
        that.healthService.resetHealthValues();
        that.healthValues = that.healthService.getHealthValues();

        //Log out user
        that.userService.logout();
        that.user = that.userService.getUser();
        that.userService.emit();
      }

      if (message["type"] == "user-identified") {
        console.log("scan-started", message["user"]);
        that.userService.setUser(message["user"]);
        that.user = that.userService.getUser();
        that.userService.emit();
      }

      if (message["type"] == "sensor-finished") {
        console.log("sensor-finished", message["data"]);
        //SerializationHelper.toInstance(that.healthValues, message["data"]);
        that.healthService.setHealthValues(message["data"]);
        that.healthValues = that.healthService.getHealthValues();
      }

      if (message["type"] == "pulse-stream") {
        console.log("pulse-stram", message["value"]);
        that.shiftPulseWave(message["value"]);
      }

      if (message["type"] == "scan-finished") {
        console.log("scan-finished");
        that.scanning = false;
        that.scanSuccessful = true;

        that.flashMessage.show(
          'Scan finished!',
          {cssClass: 'alert-success', timeout: 3000 }
        );
      }

      if (message["type"] == "scan-failed") {
        console.log("scan-failed");
        that.scanning = false;
        that.scanSuccessful = false;
        that.flashMessage.show(
          'Scan failed!',
          {cssClass: 'alert-danger', timeout: 3000 }
        );
      }

    })
  }

  private shiftPulseWave(value:number):void {
    let clone = JSON.parse(JSON.stringify(this.stressData));
    let cloneLabels = JSON.parse(JSON.stringify(this.dateLabels));
    clone[0].data.splice(0,1);
    clone[0].data.push(value)

    cloneLabels.splice(0,1);
    cloneLabels.push(1)
    this.stressData = clone;
    this.dateLabels = cloneLabels;
  }

  public register(){
    this.router.navigate(['/sign-up']);
  }

}
