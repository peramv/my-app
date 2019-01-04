package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;


import com.fasterxml.jackson.annotation.JsonInclude;

import java.util.List;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="ConfigGetResponse")
@JsonInclude(JsonInclude.Include.NON_NULL)
public class ConfigGetResponse extends BaseResponse {
    private List<Configuration> configurationList;

    public List<Configuration> getConfigurationList() {
        return configurationList;
    }

    public void setConfigurationList(List<Configuration> configurationList) {
        this.configurationList = configurationList;
    }

}

