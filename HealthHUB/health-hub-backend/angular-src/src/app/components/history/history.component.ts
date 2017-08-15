import { Component, OnInit } from '@angular/core';
import {ActivatedRoute} from '@angular/router';

@Component({
  selector: 'app-history',
  templateUrl: './history.component.html',
  styleUrls: ['./history.component.css']
})
export class HistoryComponent implements OnInit {
  //Tab-Selection
  stressActive:boolean = false;
  heartActive:boolean = false;
  tempActive:boolean = false;

  //Charts
  pulseChartOptions:any = {
    responsive: true,
    scales: {
      yAxes: [{
        ticks: {
          stepSize: 1,
          fontColor: "white"
        },
       display: true,
       scaleLabel: {
         display: true,
         labelString: 'Pulse (BPM)',
         fontColor: "white"
       }
     }],
      xAxes: [{
        type: "time",
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Date',
          fontColor: "white"
        },
        ticks: {fontColor: "white"}
      }]
    },
    legend: {labels:{fontColor:"white"}}
  };

  tempChartOptions:any = {
    responsive: true,
    scales: {
      yAxes: [{
        ticks: {
          fontColor: "white",
          stepSize: 0.1
        },
       display: true,
       scaleLabel: {
         display: true,
         labelString: 'Temperature (°C)',
         fontColor: "white"
       }
     }],
      xAxes: [{
        type: "time",
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Date',
          fontColor: "white"
        },
        ticks: {fontColor: "white"}
      }]
    },
    legend: {labels:{fontColor:"white"}}
  };
  stressChartOptions:any = {
    scaleShowVerticalLines: false,
    responsive: true,
    scales: {
      yAxes: [{
       ticks: {
         stepSize: 5,
         fontColor: "white"
       },
       display: true,
       scaleLabel: {
         display: true,
         labelString: 'Galvanic Skin Response (GSR)',
         fontColor: "white"
       }
     }],
      xAxes: [{
        type: "time",
        display: true,
        scaleLabel: {
          display: true,
          labelString: 'Date',
          fontColor: "white"
        },
        ticks: {fontColor: "white"}
      }]
    },
    legend: {labels:{fontColor:"white"}}
  };

  constructor(
    private route: ActivatedRoute
  ) {
    //Pre-select tab if tab-name is passed via query
    route.queryParams.subscribe(
      params => {
        switch(params['tab']) {
          case 'temp':
              this.tempActive = true;
              break;
          case 'heart':
              this.heartActive = true;
              break;
          case 'stress':
              this.stressActive = true;
              break;
          }
      }
    );
  }

  ngOnInit() {
  }

  // chart-data (MOCK)
  temperatureData:Array<any> = [
    {data: [37.00, 37.11, 37.10, 37.05, 36.85, 37.00, 36.90], label: 'Temperature'}
  ];
  pulseData:Array<any> = [
    {data: [78, 77, 78, 78, 82, 80, 79], label: 'Pulse'}
  ];
  stressData:any[] = [
    {data: [50, 60, 59, 70, 79, 75, 70], label: 'Stress'}
  ];

  //Chart labels, date (MOCK)
  dateLabels:string[] = [
    this.getDate(1),
    this.getDate(2),
    this.getDate(3),
    this.getDate(4),
    this.getDate(5),
    this.getDate(6),
    this.getDate(7)
  ];


  // Chartevents
  chartClicked(e:any):void {
    //console.log(e);
  }

  chartHovered(e:any):void {
    //console.log(e);
  }

  getDate(day: number){
    var date = new Date(2017, 0o4, day);
    return date.toString();
  }


}
