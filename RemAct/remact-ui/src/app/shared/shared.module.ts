import { OpenapeService } from './openape.service';
import { RestService } from './rest.service';
import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';

@NgModule({
  imports: [
    CommonModule
  ],
  declarations: [
  ],
  providers: [RestService, OpenapeService]
})
export class SharedModule { }
