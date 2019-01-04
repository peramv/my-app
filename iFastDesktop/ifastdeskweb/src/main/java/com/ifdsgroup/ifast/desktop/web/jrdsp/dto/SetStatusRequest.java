package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.util.List;

public class SetStatusRequest {
	private String status;
	List<FileRecord> records;
	
	public String getStatus() {
		return status;
	}
	public void setStatus(String status) {
		this.status = status;
	}
	public List<FileRecord> getRecords() {
		return records;
	}
	public void setRecords(List<FileRecord> records) {
		this.records = records;
	}
}
