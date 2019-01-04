package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.math.BigDecimal;

import javax.xml.bind.annotation.XmlRootElement;


public class AssociatedGrantDto {
	
	private long transNumber;
	private BigDecimal amount;
	private String paymentDate;
	private String rdspTransactionTypeCode;
	
	
	public long getTransNumber() {
		return transNumber;
	}
	public void setTransNumber(long transNumber) {
		this.transNumber = transNumber;
	}
	public BigDecimal getAmount() {
		return amount;
	}
	public void setAmount(BigDecimal amount) {
		this.amount = amount;
	}
	public String getPaymentDate() {
		return paymentDate;
	}
	public void setPaymentDate(String paymentDate) {
		this.paymentDate = paymentDate;
	}
	public String getRdspTransactionTypeCode() {
		return rdspTransactionTypeCode;
	}
	public void setRdspTransactionTypeCode(String rdspTransactionTypeCode) {
		this.rdspTransactionTypeCode = rdspTransactionTypeCode;
	}
	
	

}
