package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

public class Entity {
	
	private String name;
	
	private String sinOrBn;
	
	private String relationToBene;
	
	private String entityType;
	
	private String effectiveDate;

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getSinOrBn() {
		return sinOrBn;
	}

	public void setSinOrBn(String sinOrBn) {
		this.sinOrBn = sinOrBn;
	}

	public String getRelationToBene() {
		return relationToBene;
	}

	public void setRelationToBene(String relationToBene) {
		this.relationToBene = relationToBene;
	}
	
	public String getEntityType() {
		return entityType;
	}

	public void setEntityType(String entityType) {
		this.entityType = entityType;
	}

	public String getEffectiveDate() {
		return effectiveDate;
	}

	public void setEffectiveDate(String effectiveDate) {
		this.effectiveDate = effectiveDate;
	}

}
