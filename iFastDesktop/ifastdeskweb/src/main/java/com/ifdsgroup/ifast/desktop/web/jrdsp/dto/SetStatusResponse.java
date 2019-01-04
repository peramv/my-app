package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import static java.util.stream.Collectors.toList;

import java.util.LinkedHashMap;
import java.util.List;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="StatusResponse")
public class SetStatusResponse {
	private List<FileRecord> transaction;
	
	public List<FileRecord> getTransaction() {
		return transaction;
	}

	public void setTransaction(List<FileRecord> transaction) {
		this.transaction = transaction;
	}
	
	static public SetStatusResponse toXML(List<LinkedHashMap<String, Object>> list) {
		SetStatusResponse resp = new SetStatusResponse();
		resp.setTransaction(list.stream().map(FileRecord::new).collect(toList()));
		return resp;
	}
}