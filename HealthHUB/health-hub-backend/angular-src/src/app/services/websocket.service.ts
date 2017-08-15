import { Subject } from 'rxjs/Subject';
import { Observable } from 'rxjs/Observable';
import * as io from 'socket.io-client';

export class WebsocketService {
  // Our localhost address that we set in our server code
  private url = 'http://localhost:9080';
  private socket = io(this.url);

  sendMessage(type, message){
    this.socket.emit(type, message);
  }
  
  getMessages() {
    let observable = new Observable(observer => {
      this.socket.on('message', (data) => {
        console.log(data);
        observer.next(data);
      });
      return () => {
        this.socket.disconnect();
      };
    })
  return observable;
  }
}
