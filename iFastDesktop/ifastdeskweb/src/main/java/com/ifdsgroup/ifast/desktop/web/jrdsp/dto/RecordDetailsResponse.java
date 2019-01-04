package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.util.Map;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="RecordDetailsResponse")
public class RecordDetailsResponse extends BaseResponse{

    Map<String, String> recordDetails;

    public Map<String, String> getRecordDetails() {
        return recordDetails;
    }

    public void setRecordDetails(Map<String, String> recordDetails) {
        this.recordDetails = recordDetails;
    }
}
