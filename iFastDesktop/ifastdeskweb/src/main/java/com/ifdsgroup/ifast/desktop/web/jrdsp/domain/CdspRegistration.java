package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import java.util.List;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name = "CdspRegistration")
public class CdspRegistration {

	private List<String> transactioID;
	private String refileSupress;
	private String recodStatus;
	private String cdspRegistrationStatus;
	

	public List<String> getTransactioID() {
		return transactioID;
	}
	public void setTransactioID(List<String> transactioID) {
		this.transactioID = transactioID;
	}
	public String getRefileSupress() {
		return refileSupress;
	}
	public void setRefileSupress(String refileSupress) {
		this.refileSupress = refileSupress;
	}
	public String getRecodStatus() {
		return recodStatus;
	}
	public void setRecodStatus(String recodStatus) {
		this.recodStatus = recodStatus;
	}
	public String getCdspRegistrationStatus() {
		return cdspRegistrationStatus;
	}
	public void setCdspRegistrationStatus(String cdspRegistrationStatus) {
		this.cdspRegistrationStatus = cdspRegistrationStatus;
	}

	

}
