package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import java.math.BigDecimal;
import java.util.Date;


public class RdspNotionalTransaction {
	
	private Long transactionId;
    private Long accountNumber;
    private Long transactionNumber;
    private String transactionDate;
    private String rdspTransactionTypeCode;
    private String sourceOfTransaction;
    private BigDecimal amount;
    private String transactionStatusCode;
    private String createdDate;
    private String createdBy;
    private String modifiedDate;
    private String modifiedBy;
    private Long esdcTransactionNumber;
    private Long associatedTransactionId;
//    private String rdspTransferDetail;
//    private String ifastTransactionType;
//    private Entity entity;
//    private Account account;
    private BigDecimal contributionTotal;
//    private ReportingStatus reportingStatus;
    private Boolean esdcSent;
    private Boolean esdcResponse;
    private String paymentDate;


    public RdspNotionalTransaction() {
    }


	public Long getTransactionId() {
		return transactionId;
	}


	public void setTransactionId(Long transactionId) {
		this.transactionId = transactionId;
	}


	public Long getAccountNumber() {
		return accountNumber;
	}


	public void setAccountNumber(Long accountNumber) {
		this.accountNumber = accountNumber;
	}


	public Long getTransactionNumber() {
		return transactionNumber;
	}


	public void setTransactionNumber(Long transactionNumber) {
		this.transactionNumber = transactionNumber;
	}


	public String getTransactionDate() {
		return transactionDate;
	}


	public void setTransactionDate(String transactionDate) {
		this.transactionDate = transactionDate;
	}


	public String getRdspTransactionTypeCode() {
		return rdspTransactionTypeCode;
	}


	public void setRdspTransactionTypeCode(String rdspTransactionTypeCode) {
		this.rdspTransactionTypeCode = rdspTransactionTypeCode;
	}


	public String getSourceOfTransaction() {
		return sourceOfTransaction;
	}


	public void setSourceOfTransaction(String sourceOfTransaction) {
		this.sourceOfTransaction = sourceOfTransaction;
	}


	public BigDecimal getAmount() {
		return amount;
	}


	public void setAmount(BigDecimal amount) {
		this.amount = amount;
	}


	public String getTransactionStatusCode() {
		return transactionStatusCode;
	}


	public void setTransactionStatusCode(String transactionStatusCode) {
		this.transactionStatusCode = transactionStatusCode;
	}


	public String getCreatedDate() {
		return createdDate;
	}


	public void setCreatedDate(String createdDate) {
		this.createdDate = createdDate;
	}


	public String getCreatedBy() {
		return createdBy;
	}


	public void setCreatedBy(String createdBy) {
		this.createdBy = createdBy;
	}


	public String getModifiedDate() {
		return modifiedDate;
	}


	public void setModifiedDate(String modifiedDate) {
		this.modifiedDate = modifiedDate;
	}


	public String getModifiedBy() {
		return modifiedBy;
	}


	public void setModifiedBy(String modifiedBy) {
		this.modifiedBy = modifiedBy;
	}


	public Long getEsdcTransactionNumber() {
		return esdcTransactionNumber;
	}


	public void setEsdcTransactionNumber(Long esdcTransactionNumber) {
		this.esdcTransactionNumber = esdcTransactionNumber;
	}


	public Long getAssociatedTransactionId() {
		return associatedTransactionId;
	}


	public void setAssociatedTransactionId(Long associatedTransactionId) {
		this.associatedTransactionId = associatedTransactionId;
	}


	public BigDecimal getContributionTotal() {
		return contributionTotal;
	}


	public void setContributionTotal(BigDecimal contributionTotal) {
		this.contributionTotal = contributionTotal;
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


	public String getPaymentDate() {
		return paymentDate;
	}


	public void setPaymentDate(String paymentDate) {
		this.paymentDate = paymentDate;
	}


    

}
