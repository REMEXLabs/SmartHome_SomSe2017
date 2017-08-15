import { NgModule }             from '@angular/core';
import { RouterModule, Routes } from '@angular/router';

import { ScanStartComponent } from './components/scan-start/scan-start.component';
import { ScanDoingComponent } from './components/scan-doing/scan-doing.component';
import { HistoryComponent } from './components/history/history.component';
import { HelpComponent } from './components/help/help.component';
import { SettingsComponent } from './components/settings/settings.component';
import { LoginComponent } from './components/login/login.component';
import { SignUpComponent } from './components/sign-up/sign-up.component';
import { PageNotFoundComponent } from './components/page-not-found/page-not-found.component';

const appRoutes: Routes =  [
  {path:'', component: ScanStartComponent},
  {path:'login', component: LoginComponent},
  {path:'sign-up', component: SignUpComponent},
  {path:'scan-start', component: ScanStartComponent},
  {path:'scan-doing', component: ScanDoingComponent},
  {path:'history', component: HistoryComponent},
  {path:'help', component: HelpComponent},
  {path:'settings', component: SettingsComponent},
  {path: '404', component: PageNotFoundComponent},
  { path: '**',  redirectTo: '/404'}
]

@NgModule({
  imports: [ RouterModule.forRoot(appRoutes) ],
  exports: [ RouterModule ]
})

export class AppRoutingModule {}

export const routingComponents = [
  ScanStartComponent,
  ScanDoingComponent,
  HistoryComponent,
  HelpComponent,
  SettingsComponent,
  LoginComponent,
  SignUpComponent,
  PageNotFoundComponent
]
