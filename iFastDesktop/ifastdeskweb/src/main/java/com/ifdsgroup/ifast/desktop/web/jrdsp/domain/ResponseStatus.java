package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import java.util.ArrayList;
import java.util.List;

public class ResponseStatus {
	private String mediaType;
	private String httpMethod;
	private String httpPath;
	private String version;
	private int responseStatus;
	private List<Error> violations;

	public String getHttpPath() {
		return httpPath;
	}

	public void setHttpPath(String httpPath) {
		this.httpPath = httpPath;
	}

	public String getHttpMethod() {
		return httpMethod;
	}

	public void setHttpMethod(String httpMethod) {
		this.httpMethod = httpMethod;
	}

	public String getVersion() {
		return version;
	}

	public void setVersion(String version) {
		this.version = version;
	}

	public int getResponseStatus() {
		return responseStatus;
	}

	public void setResponseStatus(int responseStatus) {
		this.responseStatus = responseStatus;
	}

	public List<Error> getViolations() {
		return violations;
	}

	public void setViolations(List<Error> violations) {
		this.violations = violations;
	}
	
	public void addViolation(Error error) {
		if (violations == null) {
			violations = new ArrayList<Error>();
		}
		violations.add(error);
	}	

	public String getMediaType() {
		return mediaType;
	}

	public void setMediaType(String mediaType) {
		this.mediaType = mediaType;
	}
}
