import { TestBed, inject } from '@angular/core/testing';

import { OpenapeService } from './openape.service';

describe('OpenapeService', () => {
  beforeEach(() => {
    TestBed.configureTestingModule({
      providers: [OpenapeService]
    });
  });

  it('should ...', inject([OpenapeService], (service: OpenapeService) => {
    expect(service).toBeTruthy();
  }));
});
