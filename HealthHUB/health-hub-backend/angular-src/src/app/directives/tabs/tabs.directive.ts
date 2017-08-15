import { Component, ContentChildren, QueryList, AfterContentInit } from '@angular/core';
import { TabDirective } from './tab.directive';

@Component({
  selector: 'tabs',
  template:`
    <ul class="nav nav-tabs mt-20">
      <li *ngFor="let tab of tabs" (click)="selectTab(tab)" [class.active]="tab.active">
        <a>
        <span class="icon" *ngIf="tab.icon">
          <img src="/assets/img/{{tab.icon}}" />
        </span>
        {{tab.title}}
        </a>
      </li>
    </ul>
    <ng-content></ng-content>
  `,
  styles: [`
    .nav-tabs {
        border-bottom: 0px;
    }

    .nav-tabs li a {
      cursor: pointer!important;
      background-color: #3A3D42;
      color: #fff;
    }

    span.icon img {
      height: 25px;
    }

    .nav-tabs>li.active>a, .nav-tabs>li.active>a:hover, .nav-tabs>li.active>a:focus {
      border: 1px solid grey;
      background-color: #434042;
    }

    .nav-tabs>li {
        float: left;
        width: 33.33%;
    }
  `]
})
export class TabsDirective implements AfterContentInit {

  @ContentChildren(TabDirective) tabs: QueryList<TabDirective>;

  // contentChildren are set
  ngAfterContentInit() {
    // get all active tabs
    let activeTabs = this.tabs.filter((tab)=>tab.active == true);

    // if there is no active tab set, activate the first
    if(activeTabs.length === 0) {
      this.selectTab(this.tabs.first);
    }
  }

  selectTab(tab: TabDirective){
    // deactivate all tabs
    this.tabs.toArray().forEach(tab => tab.active = false);

    // activate the tab the user has clicked on.
    tab.active = true;
  }

}
