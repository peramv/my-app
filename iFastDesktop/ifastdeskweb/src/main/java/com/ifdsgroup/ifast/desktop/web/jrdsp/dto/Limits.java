package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.math.BigDecimal;

public class Limits {

	private String limitCat;
	private BigDecimal contMax;
	private BigDecimal contUsed;
	private BigDecimal contRemaining;
	private BigDecimal grantsMax;
	private BigDecimal grantsUsed;
	private BigDecimal grantsRemaining;
	private BigDecimal bondsMax;
	private BigDecimal bondsUsed;
	private BigDecimal bondsRemaining;
	
	public Limits() {}
	
	public Limits(String limitCat, BigDecimal contMax, BigDecimal contUsed, BigDecimal contRemaining,
			BigDecimal grantsMax, BigDecimal grantsUsed, BigDecimal grantsRemaining, BigDecimal bondsMax,
			BigDecimal bondsUsed, BigDecimal bondsRemaining) {
		super();
		this.limitCat = limitCat;
		this.contMax = contMax;
		this.contUsed = contUsed;
		this.contRemaining = contRemaining;
		this.grantsMax = grantsMax;
		this.grantsUsed = grantsUsed;
		this.grantsRemaining = grantsRemaining;
		this.bondsMax = bondsMax;
		this.bondsUsed = bondsUsed;
		this.bondsRemaining = bondsRemaining;
	}
	
	public String getLimitCat() {
		return limitCat;
	}
	public void setLimitCat(String limitCat) {
		this.limitCat = limitCat;
	}
	public BigDecimal getContMax() {
		return contMax;
	}
	public void setContMax(BigDecimal contMax) {
		this.contMax = contMax;
	}
	public BigDecimal getContUsed() {
		return contUsed;
	}
	public void setContUsed(BigDecimal contUsed) {
		this.contUsed = contUsed;
	}
	public BigDecimal getContRemaining() {
		return contRemaining;
	}
	public void setContRemaining(BigDecimal contRemaining) {
		this.contRemaining = contRemaining;
	}
	public BigDecimal getGrantsMax() {
		return grantsMax;
	}
	public void setGrantsMax(BigDecimal grantsMax) {
		this.grantsMax = grantsMax;
	}
	public BigDecimal getGrantsUsed() {
		return grantsUsed;
	}
	public void setGrantsUsed(BigDecimal grantsUsed) {
		this.grantsUsed = grantsUsed;
	}
	public BigDecimal getGrantsRemaining() {
		return grantsRemaining;
	}
	public void setGrantsRemaining(BigDecimal grantsRemaining) {
		this.grantsRemaining = grantsRemaining;
	}
	public BigDecimal getBondsMax() {
		return bondsMax;
	}
	public void setBondsMax(BigDecimal bondsMax) {
		this.bondsMax = bondsMax;
	}
	public BigDecimal getBondsUsed() {
		return bondsUsed;
	}
	public void setBondsUsed(BigDecimal bondsUsed) {
		this.bondsUsed = bondsUsed;
	}
	public BigDecimal getBondsRemaining() {
		return bondsRemaining;
	}
	public void setBondsRemaining(BigDecimal bondsRemaining) {
		this.bondsRemaining = bondsRemaining;
	}
}
