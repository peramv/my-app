package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import javax.xml.bind.annotation.XmlRootElement;

public class Configuration {
	
	private String confCode;
	
	private String confValue;

	public String getConfCode() {
		return confCode;
	}

	public void setConfCode(String confCode) {
		this.confCode = confCode;
	}

	public String getConfValue() {
		return confValue;
	}

	public void setConfValue(String confValue) {
		this.confValue = confValue;
	}

	@Override
	public String toString() {
		return "Configuration [confCode=" + confCode + ", confValue=" + confValue + "]";
	}
	

}
