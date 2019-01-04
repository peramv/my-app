package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="BaseResponse")
public class BaseResponse {
	
	private String statusCodeText;
	private int statusCodeValue;
	
	public String getStatusCodeText() {
		return statusCodeText;
	}
	public void setStatusCodeText(String statusCodeText) {
		this.statusCodeText = statusCodeText;
	}
	public int getStatusCodeValue() {
		return statusCodeValue;
	}
	public void setStatusCodeValue(int statusCodeValue) {
		this.statusCodeValue = statusCodeValue;
	}

}
