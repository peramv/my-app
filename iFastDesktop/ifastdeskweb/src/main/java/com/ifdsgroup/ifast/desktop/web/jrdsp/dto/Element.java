package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

public class Element {
	private String code;
	private String value;
	public Element() {}
	
	public Element(String code, String value) {
		this.code = code;
		this.value = value;
	}
	public String getCode() {
		return code;
	}
	public void setCode(String code) {
		this.code = code;
	}
	public String getValue() {
		return value;
	}
	public void setValue(String value) {
		this.value = value;
	}
}
