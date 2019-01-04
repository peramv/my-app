package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import java.math.BigDecimal;

public class RdspTransaction {
	
	private String TransactionId;
	private String TransactionType;
	private long TransNumber;
	private String NotionalCategory;
	private String Description;
	private String iFastTransactionType;
	private long accountNumber; // lower case
	private BigDecimal NotionalAmount;
	
	/*@JsonFormat
	  (shape = JsonFormat.Shape.STRING, pattern = "dd/MM/yyyy")*/
	private String TradeDate;
	
	/*@JsonFormat
	  (shape = JsonFormat.Shape.STRING, pattern = "dd/MM/yyyy")*/
	private String paymentDate; // lower case
	
	private String TransactionStatus;
	private String ESDCTransStatus;
	private long ESDCTransID;
	private String redemptionCode; // lower case
	private String depositCode; // // lower case
	

	public String getTransactionType() {
		return TransactionType;
	}

	public void setTransactionType(String transactionType) {
		TransactionType = transactionType;
	}

	public long getTransNumber() {
		return TransNumber;
	}

	public void setTransNumber(long transNumber) {
		TransNumber = transNumber;
	}

	public String getNotionalCategory() {
		return NotionalCategory;
	}

	public void setNotionalCategory(String notionalCategory) {
		NotionalCategory = notionalCategory;
	}

	public String getDescription() {
		return Description;
	}

	public void setDescription(String description) {
		Description = description;
	}

	public long getAccountNumber() {
		return accountNumber;
	}

	public void setAccountNumber(long accountNumber) {
		this.accountNumber = accountNumber;
	}

	public BigDecimal getNotionalAmount() {
		return NotionalAmount;
	}

	public void setNotionalAmount(BigDecimal notionalAmount) {
		NotionalAmount = notionalAmount;
	}

	public String getTradeDate() {
		return TradeDate;
	}

	public void setTradeDate(String tradeDate) {
		TradeDate = tradeDate;
	}

	public String getPaymentDate() {
		return paymentDate;
	}

	public void setPaymentDate(String paymentDate) {
		this.paymentDate = paymentDate;
	}

	public String getTransactionStatus() {
		return TransactionStatus;
	}

	public void setTransactionStatus(String transactionStatus) {
		TransactionStatus = transactionStatus;
	}

	public String getESDCTransStatus() {
		return ESDCTransStatus;
	}

	public void setESDCTransStatus(String eSDCTransStatus) {
		ESDCTransStatus = eSDCTransStatus;
	}

	public long getESDCTransID() {
		return ESDCTransID;
	}

	public void setESDCTransID(long eSDCTransID) {
		ESDCTransID = eSDCTransID;
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

	public String getTransactionId() {
		return TransactionId;
	}

	public void setTransactionId(String transactionId) {
		TransactionId = transactionId;
	}

	public String getiFastTransactionType() {
		return iFastTransactionType;
	}

	public void setiFastTransactionType(String iFastTransactionType) {
		this.iFastTransactionType = iFastTransactionType;
	}
	
	
	
	
	
	
	
	
	
	

}
