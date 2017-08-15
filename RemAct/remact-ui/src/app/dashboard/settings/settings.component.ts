import { RestService } from './../../shared/rest.service';
import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-settings',
  templateUrl: './settings.component.html',
  styleUrls: ['./settings.component.css']
})
export class SettingsComponent implements OnInit {
  minOutletDelay= 0;
  maxOutletDelay= 320;
  loaded = false;

  settingKeys = [
    "Config_OutletDelay",
    "Config_TimeBoundaryHourBegin",
    "Config_TimeBoundaryHourEnd"
  ];

  userInput:any = {};
  systemInput:any = {};

  currentDelay = 0;

  hours = ['00', '01', '02', '03', '04', '05', '06', '07', '08', '09', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', '21', '22', '23'];
  minutes = ['00', '15', '30', '45'];

  constructor(private restService:RestService) { }

  ngOnInit() {  
    this.settingKeys.forEach(key => {
      this.restService
        .getItemState(key)
        .subscribe(state => {
          // Check for adding zero to hours
          if(key.indexOf("TimeBoundaryHour") !== -1 && state.length == 1) {
            state = "0" + state.toString();
          }
          this.systemInput[key] = state;
          this.userInput[key] = state;
          this.loaded = true;
        });
    });
  }

  saveSettings() {
    this.settingKeys.forEach(key => {
      if(this.valueDiffers(key)) {
        this.restService
          .postCommandToItem(key, this.userInput[key])
          .subscribe(data => console.log(data));
        this.systemInput[key] = this.userInput[key];
      } 
    });
  }

  private valueDiffers(key:string) {
    return this.systemInput[key] !== this.userInput[key];
  }

  private saveValue(key:string, value:any) {
    this.restService.postCommandToItem(key, value).subscribe(data => console.log(data)); 
  }

} 
