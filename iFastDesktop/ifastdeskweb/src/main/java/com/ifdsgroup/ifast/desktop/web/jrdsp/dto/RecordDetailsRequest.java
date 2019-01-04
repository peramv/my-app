package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="RecordDetailsRequest")
public class RecordDetailsRequest {
	private Long eventId;
    private Integer rowNumber;
    
    public Long getEventId() {
        return eventId;
    }

    public void setEventId(Long eventId) {
        this.eventId = eventId;
    }

    public Integer getRowNumber() {
        return rowNumber;
    }

    public void setRowNumber(Integer rowNumber) {
        this.rowNumber = rowNumber;
    }
}
