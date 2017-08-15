import {Injectable} from "@angular/core";
import { ConnectionBackend, RequestOptions, Request, RequestOptionsArgs, Response, Http, Headers} from "@angular/http";
import {Observable} from "rxjs/Rx";
import {environment} from "../../environments/environment";

@Injectable()
export class InterceptedHttp extends Http {
    constructor(backend: ConnectionBackend, defaultOptions: RequestOptions) {
        super(backend, defaultOptions);
    }

    get(url: string, options?: RequestOptionsArgs): Observable<any> {
        url = this.updateUrl(url);
        return super.get(url, this.getRequestOptionArgs(options))
                    .map((res: Response) => res.json())
                    .catch(this.onCatch);
    }

    post(url: string, body: string, options?: RequestOptionsArgs): Observable<any> {
        url = this.updateUrl(url);
        return super.post(url, body, this.getRequestOptionArgs(options))
                    .map(res => res.json())
                    .catch(this.onCatch);
    }

    put(url: string, body: string, options?: RequestOptionsArgs): Observable<any> {
        url = this.updateUrl(url);
        return super.put(url, body, this.getRequestOptionArgs(options))
                    .map(res => res.json())
                    .catch(this.onCatch);
    }

    delete(url: string, options?: RequestOptionsArgs): Observable<any> {
        url = this.updateUrl(url);
        return super.delete(url, this.getRequestOptionArgs(options))
                    .map(res => res.json())
                    .catch(this.onCatch);
    }

    private updateUrl(req: string) {
        return  environment.origin + req;
    }

    /**
     * Request interceptor.
     */
    private requestInterceptor(): void {
        //this.loaderService.showPreloader();
    }

    /**
     * Response interceptor.
     */
    private responseInterceptor(): void {
        //this.loaderService.hidePreloader();
    }

    /**
     * Error handler.
     * @param error
     * @param caught
     * @returns {ErrorObservable}
     */
    private onCatch(error: any, caught: Observable<any>): Observable<any> {
        let errMsg: string;
        if (error instanceof Response) {
          const body = error.json() || '';
          const err = body.error || JSON.stringify(body);
          errMsg = `${error.status} - ${error.statusText || ''} ${err}`;
        } else {
          errMsg = error.message ? error.message : error.toString();
        }
        console.error(errMsg);

        return Observable.throw(errMsg);
    }

    /**
     * onSubscribeSuccess
     * @param res
     */
    private onSubscribeSuccess(res: Response): void {
    }

    /**
     * onSubscribeError
     * @param error
     */
    private onSubscribeError(error: any): void {
    }

    /**
     * onFinally
     */
    private onFinally(): void {
        this.responseInterceptor();
    }

    private getRequestOptionArgs(options?: RequestOptionsArgs) : RequestOptionsArgs {
        if (options == null) {
            options = new RequestOptions();
        }
        if (options.headers == null) {
            options.headers = new Headers();
        }
        options.headers.append('Content-Type', 'application/json');

        return options;
    }
}
