package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.util.List;

public class SetStatusRequest {
	List<FileRecord> records;
	
	public List<FileRecord> getRecords() {
		return records;
	}
	public void setRecords(List<FileRecord> records) {
		this.records = records;
	}
}
