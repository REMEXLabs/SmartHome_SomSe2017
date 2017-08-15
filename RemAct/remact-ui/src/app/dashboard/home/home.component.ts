import { RestService } from '../../shared/rest.service';
import { Component, OnInit } from '@angular/core';

const OUTLET_BORDER = 20;

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit {
  userInput = {
    isOutletOn: false,
    isDoorUnlocked: false
  };
  systemInput = {
    isOutletOn: false,
    isDoorUnlocked: false
  };

  cardTiles = [
    {title: 'Herd', cols: 1, rows: 1},
    {title: 'Tür', cols: 1, rows: 1},
    {title: 'Fenster 1', cols: 1, rows: 1},
    {title: 'Fenster 2', cols: 1, rows: 1}
  ];

  constructor(private restService: RestService) {}

  ngOnInit() {
   this.queryOutletState();
   window.setInterval(() => {
      this.queryOutletState();
      this.queryDoorState();
    }, 2000);
  }

  private queryOutletState() {
    return this.restService
      .getItemState('Edimax_Power')
      .subscribe((state: any) => {
        this.systemInput.isOutletOn = state > OUTLET_BORDER;
        this.syncOutletStates();
      });
  }

  public toggleOutlet() {
    const command = this.userInput.isOutletOn ? 'ON' : 'OFF';
    this.restService.postCommandToItem('Edimax_Switch', command).subscribe(this.subscribePostCommand);
    this.syncOutletStates();
  }

  private syncOutletStates() {
    this.userInput.isOutletOn =  this.userInput.isOutletOn || this.systemInput.isOutletOn;
  }


  private queryDoorState() {
    return this.restService
    .getItemState('Door_Unlocked')
    .subscribe((state: any) => {
      this.systemInput.isDoorUnlocked = state === 'ON';
      this.syncDoorStates();
    });
  }

  public toggleDoor() {
    const command = this.userInput.isDoorUnlocked ? 'ON' : 'OFF';
    this.restService.postCommandToItem('Door_Unlocked', command).subscribe(this.subscribePostCommand);
    this.syncOutletStates();
  }

  private syncDoorStates() {
    this.userInput.isDoorUnlocked =  this.userInput.isDoorUnlocked || this.systemInput.isDoorUnlocked;
  }

  private subscribePostCommand(response: any) {
   // console.log(response);
  }

}
