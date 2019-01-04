package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import javax.validation.Valid;

import org.springframework.validation.annotation.Validated;

@Validated
public class BaseRequest {

	@Valid
	private RequestHeader requestHeader;

	public RequestHeader getRequestHeader() {
		return requestHeader;
	}

	public void setRequestHeader(RequestHeader requestHeader) {
		this.requestHeader = requestHeader;
	}
}
