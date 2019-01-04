package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import java.io.Serializable;

public class Error implements Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = -6590776010594095860L;
	private String errorCode;
	private String errorMessage;
	private String severity;
	private String propertyPath;

	public Error() {
		this.severity = CommonConstants.SEVERITY_ERROR;
	}

	public String getErrorCode() {
		return errorCode;
	}

	public void setErrorCode(String errorCode) {
		this.errorCode = errorCode;
	}

	public String getErrorMessage() {
		return errorMessage;
	}

	public void setErrorMessage(String errorMessage) {
		this.errorMessage = errorMessage;
	}

	public String getSeverity() {
		return severity;
	}

	public void setSeverity(String severity) {
		this.severity = severity;
	}

	public String getPropertyPath() {
		return propertyPath;
	}

	public void setPropertyPath(String propertyPath) {
		this.propertyPath = propertyPath;
	}
}
