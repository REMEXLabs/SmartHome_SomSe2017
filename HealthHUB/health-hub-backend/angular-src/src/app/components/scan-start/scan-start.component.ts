import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

import { WebsocketService } from '../../services/websocket.service';

@Component({
  selector: 'app-scan-start',
  templateUrl: './scan-start.component.html',
  styleUrls: ['./scan-start.component.css']
})
export class ScanStartComponent implements OnInit {
  connection;
  message;

  constructor(
    private socketService: WebsocketService,
    private router: Router
  ) {}

  ngOnInit() {
    this.connection = this.socketService.getMessages().subscribe(message => {
      if (message["type"] == "scan-started") {
        this.router.navigate(['/scan-doing']);
      }
    })
  }
}
