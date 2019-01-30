package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.math.BigDecimal;
import java.util.List;

public class NotionalSummary {
	private List<Contributions> contributionList;
	private List<GrantsBonds> grantsBondsList;
	private BigDecimal accountIncome;

	public List<Contributions> getContributionList() {
		return contributionList;
	}

	public void setContributionList(List<Contributions> contributionList) {
		this.contributionList = contributionList;
	}

	public List<GrantsBonds> getGrantsBondsList() {
		return grantsBondsList;
	}

	public void setGrantsBondsList(List<GrantsBonds> grantsBondsList) {
		this.grantsBondsList = grantsBondsList;
	}

	public BigDecimal getAccountIncome() {
		return accountIncome;
	}

	public void setAccountIncome(BigDecimal accountIncome) {
		this.accountIncome = accountIncome;
	}
}
