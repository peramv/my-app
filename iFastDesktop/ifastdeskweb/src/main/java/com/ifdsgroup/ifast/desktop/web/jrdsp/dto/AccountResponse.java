package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import com.fasterxml.jackson.annotation.JsonInclude;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="AcctInqResponse")
@JsonInclude(JsonInclude.Include.NON_NULL)
public class AccountResponse extends BaseResponse  {
	
	private String accountId;
	
	private AccountDetails accountDetails;
	
	private Elections elections;
	
	private Elections dtcEligiblities;
	
	private EntityInfo entityInfo;
	
	private GrantBondPaymentHistory grantBondHistory;

	public String getAccountId() {
		return accountId;
	}

	public void setAccountId(String accountId) {
		this.accountId = accountId;
	}

	public AccountDetails getAccountDetails() {
		return accountDetails;
	}

	public void setAccountDetails(AccountDetails accountDetails) {
		this.accountDetails = accountDetails;
	}

	public Elections getElections() {
		return elections;
	}

	public void setElections(Elections elections) {
		this.elections = elections;
	}

	public Elections getDtcEligiblities() {
		return dtcEligiblities;
	}

	public void setDtcEligiblities(Elections dtcEligiblities) {
		this.dtcEligiblities = dtcEligiblities;
	}

	public EntityInfo getEntityInfo() {
		return entityInfo;
	}

	public void setEntityInfo(EntityInfo entityInfo) {
		this.entityInfo = entityInfo;
	}
	public GrantBondPaymentHistory getGrantBondHistory() {
		return grantBondHistory;
	}

	public void setGrantBondHistory(GrantBondPaymentHistory grantBondHistory) {
		this.grantBondHistory = grantBondHistory;
	}

	
	

}
