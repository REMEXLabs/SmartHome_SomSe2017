import {XHRBackend, Http, RequestOptions} from "@angular/http";
import {InterceptedHttp} from "../helpers/http.interceptor";

export function HttpService (xhrBackend: XHRBackend, requestOptions: RequestOptions): Http {
    return new InterceptedHttp(xhrBackend, requestOptions);
}
