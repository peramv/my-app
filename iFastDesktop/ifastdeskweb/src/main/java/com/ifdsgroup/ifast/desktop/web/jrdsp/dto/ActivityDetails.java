package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.math.BigDecimal;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="ActivityDetails")
public class ActivityDetails {
	
	private BigDecimal contributionAmount;
	private BigDecimal grantAmount;
	private BigDecimal bondAmount;
	private BigDecimal rspAmount;
	private BigDecimal respAmount;
	private String rdspTransactionTypeCode;
	private String bondPaymentDate;
	private String grantPaymentDate;
	private BigDecimal totalRolloverAmount;
	private String repaymentReason;
	
	public String getRepaymentReason() {
		return repaymentReason;
	}
	public void setRepaymentReason(String repaymentReason) {
		this.repaymentReason = repaymentReason;
	}
	private AssociatedGrantDto associatedGrant;
	
	public BigDecimal getContributionAmount() {
		return contributionAmount;
	}
	public void setContributionAmount(BigDecimal contributionAmount) {
		this.contributionAmount = contributionAmount;
	}
	public BigDecimal getGrantAmount() {
		return grantAmount;
	}
	public void setGrantAmount(BigDecimal grantAmount) {
		this.grantAmount = grantAmount;
	}
	public BigDecimal getBondAmount() {
		return bondAmount;
	}
	public void setBondAmount(BigDecimal bondAmount) {
		this.bondAmount = bondAmount;
	}
	
	public BigDecimal getRspAmount() {
		return rspAmount;
	}
	public void setRspAmount(BigDecimal rspAmount) {
		this.rspAmount = rspAmount;
	}
	public BigDecimal getRespAmount() {
		return respAmount;
	}
	public void setRespAmount(BigDecimal respAmount) {
		this.respAmount = respAmount;
	}
	public BigDecimal getTotalRolloverAmount() {
		return totalRolloverAmount;
	}
	public void setTotalRolloverAmount(BigDecimal totalRolloverAmount) {
		this.totalRolloverAmount = totalRolloverAmount;
	}
	public AssociatedGrantDto getAssociatedGrant() {
		return associatedGrant;
	}
	public void setAssociatedGrant(AssociatedGrantDto associatedGrant) {
		this.associatedGrant = associatedGrant;
	}
	public String getRdspTransactionTypeCode() {
		return rdspTransactionTypeCode;
	}
	public void setRdspTransactionTypeCode(String rdspTransactionTypeCode) {
		this.rdspTransactionTypeCode = rdspTransactionTypeCode;
	}
	public String getBondPaymentDate() {
		return bondPaymentDate;
	}
	public void setBondPaymentDate(String bondPaymentDate) {
		this.bondPaymentDate = bondPaymentDate;
	}
	public String getGrantPaymentDate() {
		return grantPaymentDate;
	}
	public void setGrantPaymentDate(String grantPaymentDate) {
		this.grantPaymentDate = grantPaymentDate;
	}
	
	
}
