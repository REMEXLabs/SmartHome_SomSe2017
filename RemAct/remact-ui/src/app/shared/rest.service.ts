import { environment } from '../../environments/environment';
import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';
import {Observable} from 'rxjs/Rx';

@Injectable()
export class RestService {
  constructor(private http:Http) {}

  public getItemState(itemName:string) {
    return this.http
      .get(environment.restBaseUrl + "/items/" + itemName)
      .map((res:Response) => res.json().state)
      .catch(this.handleError);
  }

  public postCommandToItem(itemName: string, command:any) {
    return this.http
      .post(environment.restBaseUrl + "/items/" + itemName, command)
  }

  private handleError(err:Response | any) {
    // TODO: Error Handling
    return Observable.throw(err)
  }
}