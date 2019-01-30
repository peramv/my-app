package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import java.util.List;

public class CDSPRegistrationRequest {

	
	private List<String> transactioID;
	private String refileSupress;
	
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
}
