package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.util.List;
import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="TransactionsRecordsResponse")
public class TransactionsRecordsResponse extends BaseResponse {
	private List<TransRecordDto> records;

	public List<TransRecordDto> getRecords() {
		return records;
	}

	public void setRecords(List<TransRecordDto> records) {
		this.records = records;
	}
}
