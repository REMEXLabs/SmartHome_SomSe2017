import { Injectable } from '@angular/core';

import { User } from '../models/user.model';
import { HealthValues } from '../models/user-health-values.model';

import { SerializationHelper } from '../helpers/serialization.helper';

@Injectable()
export class HealthValueService {
  healthValues = new HealthValues();

  constructor() { }

  setHealthValues(data){
    SerializationHelper.toInstance(this.healthValues, data);
    //this.healthValues = JSON.parse(data);
  }

  getHealthValues(){
    return this.healthValues;
  }

  resetHealthValues(){
    this.healthValues = new HealthValues();
  }

}
