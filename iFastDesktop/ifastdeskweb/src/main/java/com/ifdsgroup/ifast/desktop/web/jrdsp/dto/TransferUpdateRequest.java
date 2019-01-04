package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.math.BigDecimal;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="TransferUpdateRequest")
public class TransferUpdateRequest {
	private String accountNumber;
	private String transactionId;
	private String extRDSPContNum;
	private String extSpecimenPlanNum;	
	private String internalRDSPContNum;
	private String internalSpecimenPlanNum;
	private BigDecimal nonTaxablePrivateCntbns;	
	private BigDecimal canadaDisabilitySavingsGrant;
	private BigDecimal taxableReportsRollovers;
	private BigDecimal canadaDisabilitySavingsBond;	
	private BigDecimal fairMarketValue;
	private BigDecimal grantBondsPaid;
	private BigDecimal contributions;	
	private BigDecimal nonTaxablePriorDapLdap;
	private BigDecimal nonTaxablePresentDapLdap;
	private BigDecimal taxablePriorDapLdap;
	private BigDecimal taxablePresentDapLdap;
	private Boolean formEditableFlag;
    private Boolean esdcSent;
    private Boolean esdcResponse;
    private Boolean moneyOutTrade;
    private String transferInStatusTypeCode;
    
	public String getAccountNumber() {
		return accountNumber;
	}
	public void setAccountNumber(String accountNumber) {
		this.accountNumber = accountNumber;
	}
	public String getTransactionId() {
		return transactionId;
	}
	public void setTransactionId(String transactionId) {
		this.transactionId = transactionId;
	}
	public String getExtRDSPContNum() {
		return extRDSPContNum;
	}
	public void setExtRDSPContNum(String extRDSPContNum) {
		this.extRDSPContNum = extRDSPContNum;
	}
	public String getExtSpecimenPlanNum() {
		return extSpecimenPlanNum;
	}
	public void setExtSpecimenPlanNum(String extSpecimenPlanNum) {
		this.extSpecimenPlanNum = extSpecimenPlanNum;
	}
	public String getInternalRDSPContNum() {
		return internalRDSPContNum;
	}
	public void setInternalRDSPContNum(String internalRDSPContNum) {
		this.internalRDSPContNum = internalRDSPContNum;
	}
	public String getInternalSpecimenPlanNum() {
		return internalSpecimenPlanNum;
	}
	public void setInternalSpecimenPlanNum(String internalSpecimenPlanNum) {
		this.internalSpecimenPlanNum = internalSpecimenPlanNum;
	}
	public BigDecimal getNonTaxablePrivateCntbns() {
		return nonTaxablePrivateCntbns;
	}
	public void setNonTaxablePrivateCntbns(BigDecimal nonTaxablePrivateCntbns) {
		this.nonTaxablePrivateCntbns = nonTaxablePrivateCntbns;
	}
	public BigDecimal getCanadaDisabilitySavingsGrant() {
		return canadaDisabilitySavingsGrant;
	}
	public void setCanadaDisabilitySavingsGrant(BigDecimal canadaDisabilitySavingsGrant) {
		this.canadaDisabilitySavingsGrant = canadaDisabilitySavingsGrant;
	}
	public BigDecimal getTaxableReportsRollovers() {
		return taxableReportsRollovers;
	}
	public void setTaxableReportsRollovers(BigDecimal taxableReportsRollovers) {
		this.taxableReportsRollovers = taxableReportsRollovers;
	}
	public BigDecimal getCanadaDisabilitySavingsBond() {
		return canadaDisabilitySavingsBond;
	}
	public void setCanadaDisabilitySavingsBond(BigDecimal canadaDisabilitySavingsBond) {
		this.canadaDisabilitySavingsBond = canadaDisabilitySavingsBond;
	}
	public BigDecimal getFairMarketValue() {
		return fairMarketValue;
	}
	public void setFairMarketValue(BigDecimal fairMarketValue) {
		this.fairMarketValue = fairMarketValue;
	}
	public BigDecimal getGrantBondsPaid() {
		return grantBondsPaid;
	}
	public void setGrantBondsPaid(BigDecimal grantBondsPaid) {
		this.grantBondsPaid = grantBondsPaid;
	}
	public BigDecimal getContributions() {
		return contributions;
	}
	public void setContributions(BigDecimal contributions) {
		this.contributions = contributions;
	}
	public BigDecimal getNonTaxablePriorDapLdap() {
		return nonTaxablePriorDapLdap;
	}
	public void setNonTaxablePriorDapLdap(BigDecimal nonTaxablePriorDapLdap) {
		this.nonTaxablePriorDapLdap = nonTaxablePriorDapLdap;
	}
	public BigDecimal getNonTaxablePresentDapLdap() {
		return nonTaxablePresentDapLdap;
	}
	public void setNonTaxablePresentDapLdap(BigDecimal nonTaxablePresentDapLdap) {
		this.nonTaxablePresentDapLdap = nonTaxablePresentDapLdap;
	}
	public BigDecimal getTaxablePriorDapLdap() {
		return taxablePriorDapLdap;
	}
	public void setTaxablePriorDapLdap(BigDecimal taxablePriorDapLdap) {
		this.taxablePriorDapLdap = taxablePriorDapLdap;
	}
	public BigDecimal getTaxablePresentDapLdap() {
		return taxablePresentDapLdap;
	}
	public void setTaxablePresentDapLdap(BigDecimal taxablePresentDapLdap) {
		this.taxablePresentDapLdap = taxablePresentDapLdap;
	}
	public Boolean getFormEditableFlag() {
		return formEditableFlag;
	}
	public void setFormEditableFlag(Boolean formEditableFlag) {
		this.formEditableFlag = formEditableFlag;
	}
	public Boolean getEsdcSent() {
		return esdcSent;
	}
	public void setEsdcSent(Boolean esdcSent) {
		this.esdcSent = esdcSent;
	}
	public Boolean getEsdcResponse() {
		return esdcResponse;
	}
	public void setEsdcResponse(Boolean esdcResponse) {
		this.esdcResponse = esdcResponse;
	}
	public Boolean getMoneyOutTrade() {
		return moneyOutTrade;
	}
	public void setMoneyOutTrade(Boolean moneyOutTrade) {
		this.moneyOutTrade = moneyOutTrade;
	}
	public String getTransferInStatusTypeCode() {
		return transferInStatusTypeCode;
	}
	public void setTransferInStatusTypeCode(String transferInStatusTypeCode) {
		this.transferInStatusTypeCode = transferInStatusTypeCode;
	}
	
	
}
