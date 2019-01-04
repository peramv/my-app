package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.util.List;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlElementWrapper;
import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="notionalBalanceResponse")
public class NotionalBalanceResponse {
	private long accountNumber;
	private String beneName;
	private String inceptionDate;
	
	private List<Contributions> contributionsList;
	private List<GrantsBonds> grantsBondsList;
	private List<Limits> limitsList;
	private com.ifdsgroup.ifast.desktop.web.jrdsp.dto.ElementList list;
	
	public long getAccountNumber() {
		return accountNumber;
	}
	public void setAccountNumber(long accountNumber) {
		this.accountNumber = accountNumber;
	}
	public String getBeneName() {
		return beneName;
	}
	public void setBeneName(String beneName) {
		this.beneName = beneName;
	}
	public String getInceptionDate() {
		return inceptionDate;
	}
	public void setInceptionDate(String inceptionDate) {
		this.inceptionDate = inceptionDate;
	}
	public com.ifdsgroup.ifast.desktop.web.jrdsp.dto.ElementList getList() {
		return list;
	}
	public void setList(com.ifdsgroup.ifast.desktop.web.jrdsp.dto.ElementList list) {
		this.list = list;
	}
	@XmlElementWrapper(name="grantsBondsList")
	@XmlElement(name="grantsBonds")
	public List<GrantsBonds> getGrantsBondsList() {
		return grantsBondsList;
	}
	public void setGrantsBondsList(List<GrantsBonds> grantsBondsList) {
		this.grantsBondsList = grantsBondsList;
	}
	@XmlElementWrapper(name="limitsList")
	@XmlElement(name="limits")
	public List<Limits> getLimitsList() {
		return limitsList;
	}
	public void setLimitsList(List<Limits> limitsList) {
		this.limitsList = limitsList;
	}
	public void setContributionsList(List<Contributions> contributionsList) {
		this.contributionsList = contributionsList;
	}
	@XmlElementWrapper(name="contributionsList")
	@XmlElement(name="contributions")
	public List<Contributions> getContributionsList() {
		return contributionsList;
	}	
}

