package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import com.fasterxml.jackson.annotation.JsonInclude;

import java.util.List;

import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

@XmlRootElement(name="ConfigurationResponse")
@JsonInclude(JsonInclude.Include.NON_NULL)
public class ConfigurationResponse extends BaseResponse  {
	private ConfigurationList configList;

	public ConfigurationList getConfigList() {
		return configList;
	}

	public void setConfigList(ConfigurationList configList) {
		this.configList = configList;
	}
	
  
	

}
