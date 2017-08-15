import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpModule, Http, XHRBackend, RequestOptions } from '@angular/http';

import { FlashMessagesModule } from 'angular2-flash-messages';
import { ChartsModule } from 'ng2-charts/ng2-charts';
import { SwiperModule } from 'angular2-useful-swiper';

import { AppComponent } from './app.component';

import { AppRoutingModule, routingComponents }    from './app-routing.module';
import { NavbarComponent } from './components/navbar/navbar.component';

import { HttpService } from './services/http.service';
import { WebsocketService } from './services/websocket.service';
import { UserService } from './services/user.service';
import { HealthValueService } from './services/health-value.service';

import { TabDirective } from './directives/tabs/tab.directive';
import { TabsDirective } from './directives/tabs/tabs.directive';

@NgModule({
  declarations: [
    AppComponent,
    NavbarComponent,
    routingComponents,
    TabDirective,
    TabsDirective
  ],
  imports: [
    BrowserModule,
    FormsModule,
    HttpModule,
    AppRoutingModule,
    FlashMessagesModule,
    ChartsModule,
    SwiperModule
  ],
  providers: [
        {
            provide: Http,
            useFactory: HttpService,
            deps: [XHRBackend, RequestOptions]
        },
        WebsocketService,
        HealthValueService,
        UserService
    ],
  bootstrap: [AppComponent]
})
export class AppModule { }
