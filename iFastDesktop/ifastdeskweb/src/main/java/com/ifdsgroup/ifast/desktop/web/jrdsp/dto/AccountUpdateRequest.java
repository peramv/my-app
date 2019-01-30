package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import javax.xml.bind.annotation.XmlRootElement;
import java.util.List;

@XmlRootElement(name="AcctUpdateRequest")
public class AccountUpdateRequest {

	private String inceptionDate;

	private String grantRequested;

	private String grantDate;
	
	private String bondRequested;

	private String transferredAccount;

	private String reportToESDC;

	private String dtcEligible;

	private String specifiedYear;

	private String contractStatusRegistration;

	private String dtcElection;

	private String sdspElection;

	private String closureReasonCode;

	private String accountStatus;

	private String closureDate;

	private String createdBy;

	private String accountUuid;

	private Elections elections;

	public String getInceptionDate() {
		return inceptionDate;
	}

	public void setInceptionDate(String inceptionDate) {
		this.inceptionDate = inceptionDate;
	}

	public String getGrantRequested() {
		return grantRequested;
	}

	public void setGrantRequested(String grantRequested) {
		this.grantRequested = grantRequested;
	}

	public String getBondRequested() {
		return bondRequested;
	}

	public void setBondRequested(String bondRequested) {
		this.bondRequested = bondRequested;
	}

	public String getTransferredAccount() {
		return transferredAccount;
	}

	public void setTransferredAccount(String transferredAccount) {
		this.transferredAccount = transferredAccount;
	}

	public String getReportToESDC() {
		return reportToESDC;
	}

	public void setReportToESDC(String reportToESDC) {
		this.reportToESDC = reportToESDC;
	}

	public String getDtcEligible() {
		return dtcEligible;
	}

	public void setDtcEligible(String dtcEligible) {
		this.dtcEligible = dtcEligible;
	}

	public String getSpecifiedYear() {
		return specifiedYear;
	}

	public void setSpecifiedYear(String specifiedYear) {
		this.specifiedYear = specifiedYear;
	}

	public String getContractStatusRegistration() {
		return contractStatusRegistration;
	}

	public void setContractStatusRegistration(String contractStatusRegistration) {
		this.contractStatusRegistration = contractStatusRegistration;
	}

	public String getDtcElection() {
		return dtcElection;
	}

	public void setDtcElection(String dtcElection) {
		this.dtcElection = dtcElection;
	}

	public String getSdspElection() {
		return sdspElection;
	}

	public void setSdspElection(String sdspElection) {
		this.sdspElection = sdspElection;
	}

	public String getClosureReasonCode() {
		return closureReasonCode;
	}

	public void setClosureReasonCode(String closureReasonCode) {
		this.closureReasonCode = closureReasonCode;
	}

	public String getAccountStatus() {
		return accountStatus;
	}

	public void setAccountStatus(String accountStatus) {
		this.accountStatus = accountStatus;
	}

	public String getClosureDate() {
		return closureDate;
	}

	public void setClosureDate(String closureDate) {
		this.closureDate = closureDate;
	}

	public String getCreatedBy() {
		return createdBy;
	}

	public void setCreatedBy(String createdBy) {
		this.createdBy = createdBy;
	}

	public String getAccountUuid() {
		return accountUuid;
	}

	public void setAccountUuid(String accountUuid) {
		this.accountUuid = accountUuid;
	}
	public Elections getElections() {
		return elections;
	}

	public void setElections(Elections elections) {
		this.elections = elections;
	}
	
	public String getGrantDate() {
		return grantDate;
	}

	public void setGrantDate(String grantDate) {
		this.grantDate = grantDate;
	}
}
