package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

public class ResponseHeader {
	private RecordRange recordRange;
	private ResponseStatus responseStatus;

	public RecordRange getRecordRange() {
		return recordRange;
	}

	public void setRecordRange(RecordRange recordRange) {
		this.recordRange = recordRange;
	}

	public ResponseStatus getResponseStatus() {
		return responseStatus;
	}

	public void setResponseStatus(ResponseStatus responseStatus) {
		this.responseStatus = responseStatus;
	}

}
