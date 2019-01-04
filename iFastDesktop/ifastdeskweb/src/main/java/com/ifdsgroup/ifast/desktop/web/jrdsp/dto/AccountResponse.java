package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import com.fasterxml.jackson.annotation.JsonInclude;

import java.util.List;

import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

@XmlRootElement(name="AcctInqResponse")
@JsonInclude(JsonInclude.Include.NON_NULL)
public class AccountResponse extends BaseResponse  {
	
	private String accountId;
	
	private AccountDetails accountDetails;
	
	private Elections elections;
	
	private EntityInfo entityInfo;

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

	public EntityInfo getEntityInfo() {
		return entityInfo;
	}

	public void setEntityInfo(EntityInfo entityInfo) {
		this.entityInfo = entityInfo;
	}


	//private List<AccountEntity> entityList;
	
	

}
