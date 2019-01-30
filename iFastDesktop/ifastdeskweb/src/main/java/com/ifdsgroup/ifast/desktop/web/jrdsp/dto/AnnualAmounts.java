package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.math.BigDecimal;

public class AnnualAmounts {

	private BigDecimal taxExemptionBalance;
	private BigDecimal taxableRedemptions;
	private BigDecimal sdspMaxTaxablePortion;
	private BigDecimal jan1Fmv;
	private BigDecimal ldapMax;
	private Boolean pgap;
	private BigDecimal pgapMax;

	public BigDecimal getJan1Fmv() {
		return jan1Fmv;
	}

	public BigDecimal getLdapMax() {
		return ldapMax;
	}

	public Boolean getPgap() {
		return pgap;
	}

	public BigDecimal getPgapMax() {
		return pgapMax;
	}

	public BigDecimal getSdspMaxTaxablePortion() {
		return sdspMaxTaxablePortion;
	}

	public BigDecimal getTaxableRedemptions() {
		return taxableRedemptions;
	}

	public BigDecimal getTaxExemptionBalance() {
		return taxExemptionBalance;
	}

	public void setJan1Fmv(BigDecimal jan1Fmv) {
		this.jan1Fmv = jan1Fmv;
	}

	public void setLdapMax(BigDecimal ldapMax) {
		this.ldapMax = ldapMax;
	}

	public void setPgap(Boolean pgap) {
		this.pgap = pgap;
	}

	public void setPgapMax(BigDecimal pgapMax) {
		this.pgapMax = pgapMax;
	}

	public void setSdspMaxTaxablePortion(BigDecimal sdspMaxTaxablePortion) {
		this.sdspMaxTaxablePortion = sdspMaxTaxablePortion;
	}

	public void setTaxableRedemptions(BigDecimal taxableRedemptions) {
		this.taxableRedemptions = taxableRedemptions;
	}

	public void setTaxExemptionBalance(BigDecimal taxExemptionBalance) {
		this.taxExemptionBalance = taxExemptionBalance;
	}
}
