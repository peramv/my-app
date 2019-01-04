package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import java.io.Serializable;
import java.math.BigDecimal;
import java.util.Date;

import javax.xml.bind.annotation.XmlRootElement;

import com.fasterxml.jackson.annotation.JsonFormat;


public class TransactionGetResponseDto implements Serializable{
	
	private long transactionId;
	private long transactionNumber;
	private String ifastTransactionTypeCode;
	private String rdspTransactionTypeCode;
	private long accountNumber;
	private BigDecimal amount;
	/*@JsonFormat
	  (shape = JsonFormat.Shape.STRING, pattern = "dd/MM/yyyy")*/
	private String effectiveDate;
	/*@JsonFormat
	  (shape = JsonFormat.Shape.STRING, pattern = "dd/MM/yyyy")*/
	private String paymentDate;
	private String transactionStatusCode;
	private String esdcReportingStatusCode;
	private long esdcTransactionNumber;
	private String redemptionCode;
	private String depositCode;
	public long getTransactionId() {
		return transactionId;
	}
	public void setTransactionId(long transactionId) {
		this.transactionId = transactionId;
	}
	public long getTransactionNumber() {
		return transactionNumber;
	}
	public void setTransactionNumber(long transactionNumber) {
		this.transactionNumber = transactionNumber;
	}
	public String getIfastTransactionTypeCode() {
		return ifastTransactionTypeCode;
	}
	public void setIfastTransactionTypeCode(String ifastTransactionTypeCode) {
		this.ifastTransactionTypeCode = ifastTransactionTypeCode;
	}
	public String getRdspTransactionTypeCode() {
		return rdspTransactionTypeCode;
	}
	public void setRdspTransactionTypeCode(String rdspTransactionTypeCode) {
		this.rdspTransactionTypeCode = rdspTransactionTypeCode;
	}
	public long getAccountNumber() {
		return accountNumber;
	}
	public void setAccountNumber(long accountNumber) {
		this.accountNumber = accountNumber;
	}
	public BigDecimal getAmount() {
		return amount;
	}
	public void setAmount(BigDecimal amount) {
		this.amount = amount;
	}
	public String getEffectiveDate() {
		return effectiveDate;
	}
	public void setEffectiveDate(String effectiveDate) {
		this.effectiveDate = effectiveDate;
	}
	public String getPaymentDate() {
		return paymentDate;
	}
	public void setPaymentDate(String paymentDate) {
		this.paymentDate = paymentDate;
	}
	public String getTransactionStatusCode() {
		return transactionStatusCode;
	}
	public void setTransactionStatusCode(String transactionStatusCode) {
		this.transactionStatusCode = transactionStatusCode;
	}
	public String getEsdcReportingStatusCode() {
		return esdcReportingStatusCode;
	}
	public void setEsdcReportingStatusCode(String esdcReportingStatusCode) {
		this.esdcReportingStatusCode = esdcReportingStatusCode;
	}
	public long getEsdcTransactionNumber() {
		return esdcTransactionNumber;
	}
	public void setEsdcTransactionNumber(long esdcTransactionNumber) {
		this.esdcTransactionNumber = esdcTransactionNumber;
	}
	public String getRedemptionCode() {
		return redemptionCode;
	}
	public void setRedemptionCode(String redemptionCode) {
		this.redemptionCode = redemptionCode;
	}
	public String getDepositCode() {
		return depositCode;
	}
	public void setDepositCode(String depositCode) {
		this.depositCode = depositCode;
	}
		
}
