package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.util.List;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="Request")
public class StatusUpdateRequest {
	List<FileRecord> record;

	public List<FileRecord> getRecord() {
		return record;
	}
	public void setRecord(List<FileRecord> record) {
		this.record = record;
	}
}
