package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

public class NotionalGetRequest {
	
	private String accountNumber;
	private String transactionId;
	
	
	public NotionalGetRequest() {
		super();
	}
	public NotionalGetRequest(String accountNumber, String transactionId) {
		super();
		this.accountNumber = accountNumber;
		this.transactionId = transactionId;
	}
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
	
	
	

}
