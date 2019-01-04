package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;


public enum EntityType{
	ACCOUNT_HOLDER("01"), BENEFICIARY("79"), PRIMARY_CAREGIVER("80");
	
	private EntityType(String code) {
		this.code = code;
	}
	
	private String code;
	
	public String getCode() {
		return code;
	}
}
