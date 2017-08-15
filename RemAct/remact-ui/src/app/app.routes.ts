import { SettingsComponent } from './dashboard/settings/settings.component';
import { HomeComponent } from './dashboard/home/home.component';
import {Routes} from "@angular/router";

export const appRoutes: Routes = [
  { path: 'dashboard', component: HomeComponent },
  { path: 'settings', component: SettingsComponent },
  { path: '**', component: HomeComponent }
];