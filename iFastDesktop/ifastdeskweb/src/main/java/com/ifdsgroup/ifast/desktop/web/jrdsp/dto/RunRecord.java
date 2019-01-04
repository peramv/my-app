package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.LinkedHashMap;

public class RunRecord {
	long eventId;
	String date;
	String type;
	String description;
	
	public RunRecord() {
	}
	
	public RunRecord(LinkedHashMap<String, Object> map) {
		eventId = ((Number) map.get("eventId")).longValue();
		type = (String) map.get("type");
		
		try {
			Date dt = new SimpleDateFormat("dd/MM/yyyy").parse((String) map.get("date"));
			date = String.format("-%s-", new SimpleDateFormat("dd MMM yyyy").format(dt));
		} catch (ParseException exc) {
			throw new IllegalArgumentException(exc.getMessage());
		}
	}
		
	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public long getEventId() {
		return eventId;
	}
	
	public void setEventId(long eventId) {
		this.eventId = eventId;
	}
	
	public String getDate() {
		return date;
	}
	
	public void setDate(String date) {
		this.date = date;
	}
	
	public String getType() {
		return type;
	}
	
	public void setType(String type) {
		this.type = type;
	}
}

