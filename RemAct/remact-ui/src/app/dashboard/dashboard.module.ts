import { FormsModule } from '@angular/forms';
import { MaterialModule } from '@angular/material';
import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HomeComponent } from './home/home.component';
import { SettingsComponent } from './settings/settings.component';

@NgModule({
  imports: [
    CommonModule,
    MaterialModule,
    FormsModule
  ],
  declarations: [HomeComponent, SettingsComponent],
  exports: [HomeComponent]
})
export class DashboardModule { }
