import { async, ComponentFixture, TestBed } from '@angular/core/testing';

import { ScanDoingComponent } from './scan-doing.component';

describe('ScanFinishedComponent', () => {
  let component: ScanDoingComponent;
  let fixture: ComponentFixture<ScanDoingComponent>;

  beforeEach(async(() => {
    TestBed.configureTestingModule({
      declarations: [ ScanDoingComponent ]
    })
    .compileComponents();
  }));

  beforeEach(() => {
    fixture = TestBed.createComponent(ScanDoingComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
