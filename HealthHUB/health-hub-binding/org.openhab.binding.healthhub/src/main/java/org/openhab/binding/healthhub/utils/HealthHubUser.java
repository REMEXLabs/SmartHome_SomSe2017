package org.openhab.binding.healthhub.utils;

import java.util.Date;

public class HealthHubUser {
    private String lastname;
    private String firstname;
    private String pulse;
    private String temp;
    private String stress;
    private boolean thirdPartyAccess;
    private Date scandate;

    public String getLastname() {
        return lastname;
    }

    public void setLastname(String lastname) {
        this.lastname = lastname;
    }

    public String getFirstname() {
        return firstname;
    }

    public void setFirstname(String firstname) {
        this.firstname = firstname;
    }

    public String getPulse() {
        return pulse;
    }

    public void setPulse(String pulse) {
        this.pulse = pulse;
    }

    public String getTemp() {
        return temp;
    }

    public void setTemp(String temp) {
        this.temp = temp;
    }

    public String getStress() {
        return stress;
    }

    public void setStress(String stress) {
        this.stress = stress;
    }

    public String getFullName() {
        return firstname + " " + lastname;
    }

    public Date getScanDate() {
        return scandate;
    }

    public void setScanDate(Date scandate) {
        this.scandate = scandate;
    }

    public boolean isThirdPartyAccess() {
        return thirdPartyAccess;
    }

    public void setThirdPartyAccess(boolean thirdPartyAccess) {
        this.thirdPartyAccess = thirdPartyAccess;
    }
}
