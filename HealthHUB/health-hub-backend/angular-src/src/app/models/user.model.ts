export class User {
  id: string;
  firstname: string;
  lastname: string;
  technicalAffinity: string;
  thirdPartyAccess: boolean;

  constructor(){
    this.id = null;
    this.firstname = null;
    this.lastname = null;
    this.technicalAffinity = 'high';
    this.thirdPartyAccess = false;
  }
}
