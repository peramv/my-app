package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.math.BigDecimal;

public class GrantsBonds {
	private String category;
	private BigDecimal received;
	private BigDecimal paidOut;
	private BigDecimal repayment;
	private BigDecimal balance;
	public GrantsBonds() {}
	public GrantsBonds(String category, BigDecimal received, BigDecimal paidOut, BigDecimal repayment,
			BigDecimal balance) {
		this.category = category;
		this.received = received;
		this.paidOut = paidOut;
		this.repayment = repayment;
		this.balance = balance;
	}
	
	public String getCategory() {
		return category;
	}
	public void setCategory(String category) {
		this.category = category;
	}
	public BigDecimal getReceived() {
		return received;
	}
	public void setReceived(BigDecimal received) {
		this.received = received;
	}
	public BigDecimal getPaidOut() {
		return paidOut;
	}
	public void setPaidOut(BigDecimal paidOut) {
		this.paidOut = paidOut;
	}
	public BigDecimal getRepayment() {
		return repayment;
	}
	public void setRepayment(BigDecimal repayment) {
		this.repayment = repayment;
	}
	public BigDecimal getBalance() {
		return balance;
	}
	public void setBalance(BigDecimal balance) {
		this.balance = balance;
	}
}
