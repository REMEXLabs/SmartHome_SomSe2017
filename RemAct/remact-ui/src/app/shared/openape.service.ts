import { Observable } from 'rxjs/Rx';
import { RestService } from './rest.service';
import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';

@Injectable()
export class OpenapeService {
  private userContext = "59394a3f38f5537b5d9e103a";
  private url = "http://dev.openape.gpii.eu:8080/api";

  constructor(private http:Http) { }

  getPreferences(user:string) {
    return this.http
      .get(this.url + "/user-contexts/" + this.userContext)
      .map((res:Response) => {
        return this.parseResponse(user, res.json())
      })
      .catch(this.handleError);
  }

  private parseResponse(user:string, res:any) {
    if(!(user in res.contexts)) {
      throw Error(user + " does not exist");
    }
    return res.contexts[user].preferences;
  }

  private handleError(err:Response | any) {
    // TODO: Error H
    return Observable.throw(err)
  }

}
