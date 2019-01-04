package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.util.LinkedHashMap;

public class FileRecord {
	private long id;
	private int row;
	private boolean success;
	
	public FileRecord() {
	}
	
	public FileRecord(LinkedHashMap<String, Object> map) {
		id = ((Number) map.get("id")).longValue();
		row = (Integer) map.get("row");
		success = (Boolean) map.get("success");
	}
	
	public boolean isSuccess() {
		return success;
	}
	public void setSuccess(boolean success) {
		this.success = success;
	}
	public long getId() {
		return id;
	}
	public void setId(long id) {
		this.id = id;
	}
	public int getRow() {
		return row;
	}
	public void setRow(int row) {
		this.row = row;
	}
}

