import { OpenapeService } from './shared/openape.service';
import { Component, OnInit } from '@angular/core';


@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
  title = 'RemAct UI';
 
  userSettingsClasses = {
    "toolbar-color-green": false,
    "toolbar-color-red": false,
    "font-size-small" : false,
    "font-size-large" : false,
    "night-mode": false,
    "strong-contrast": false
  }

  constructor(private openape:OpenapeService) {}

  ngOnInit() {
    this.loadUserSettings();
  }

  private loadUserSettings() {
      this.openape
      .getPreferences("Ingobert")
      .subscribe((preferences:any) => {
        for(let i in preferences) {
          this.userSettingsClasses[i] = (preferences[i] == 'true');
        }
        //console.log(this.userSettingsClasses)
      });
  }

}
