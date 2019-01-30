package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.math.BigDecimal;

public class NotionalAnnualAmounts {
	private AnnualAmounts annualAmounts;
	private BigDecimal ahaAmount;
	private boolean sdspAccount;
	private boolean endDateSameYearAsInception;
	
	public AnnualAmounts getAnnualAmounts() {
		return annualAmounts;
	}

	public void setAnnualAmounts(AnnualAmounts annualAmounts) {
		this.annualAmounts = annualAmounts;
	}

	public BigDecimal getAhaAmount() {
		return ahaAmount;
	}

	public void setAhaAmount(BigDecimal ahaAmount) {
		this.ahaAmount = ahaAmount;
	}

	public boolean isSdspAccount() {
		return sdspAccount;
	}

	public void setSdspAccount(boolean sdspAccount) {
		this.sdspAccount = sdspAccount;
	}

	public boolean isEndDateSameYearAsInception() {
		return endDateSameYearAsInception;
	}

	public void setEndDateSameYearAsInception(boolean endDateSameYearAsInception) {
		this.endDateSameYearAsInception = endDateSameYearAsInception;
	}
}
