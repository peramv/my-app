package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

public enum EntityRelation {
	SF("Self"),
	FM("Qualified Family Member"),
	GD("Guardian"),
	TR("Tutor"),
	CR("Curator"),
	LP("Legal Parent"),
	PD("Public Department"),
	AG("Agency"),
	IT("Institution"),
	LR("Legal Representative");
	
	private EntityRelation(String code) {
		this.code = code;
	}
	
	private String code;
	
	public String getCode() {
		return code;
	}

}
