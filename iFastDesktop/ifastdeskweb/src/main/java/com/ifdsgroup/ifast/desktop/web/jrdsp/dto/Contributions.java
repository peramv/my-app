package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.math.BigDecimal;

public class Contributions {
	private String contCategory;
	private BigDecimal purchases;
	private BigDecimal redemptions;
	private BigDecimal contBalance;
	public Contributions(String contCategory, BigDecimal purchases, BigDecimal redemptions, BigDecimal contBalance) {
		super();
		this.contCategory = contCategory;
		this.purchases = purchases;
		this.redemptions = redemptions;
		this.contBalance = contBalance;
	}	
	public Contributions() {}
	public String getContCategory() {
		return contCategory;
	}
	public void setContCategory(String contCategory) {
		this.contCategory = contCategory;
	}
	public BigDecimal getPurchases() {
		return purchases;
	}
	public void setPurchases(BigDecimal purchases) {
		this.purchases = purchases;
	}
	public BigDecimal getRedemptions() {
		return redemptions;
	}
	public void setRedemptions(BigDecimal redemptions) {
		this.redemptions = redemptions;
	}
	public BigDecimal getContBalance() {
		return contBalance;
	}
	public void setContBalance(BigDecimal contBalance) {
		this.contBalance = contBalance;
	}
}
