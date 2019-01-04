package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import java.util.List;



public class EntityGetResponse extends BaseResponse {
	
	List<AccountEntityDto> entities;

	public List<AccountEntityDto> getEntities() {
		return entities;
	}

	public void setEntities(List<AccountEntityDto> entities) {
		this.entities = entities;
	}

}
