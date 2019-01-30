package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import com.ifdsgroup.ifast.desktop.web.jrdsp.domain.CdspRegistration;

public class CDSPRegistrationResponse extends BaseResponse{
	
	private CdspRegistration cdspRegistration;
	private Integer status;

	public CdspRegistration getCdspRegistration() {
		return cdspRegistration;
	}

	public void setCdspRegistration(CdspRegistration cdspRegistration) {
		this.cdspRegistration = cdspRegistration;
	}
	
	public Integer getStatus() {
		return status;
	}

	public void setStatus(Integer status) {
		this.status = status;
	}

}
