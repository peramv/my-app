package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import java.math.BigDecimal;

public class NotionalLotActivityBalancesDto {

    private BigDecimal contributionAmount;
    private BigDecimal grantAmount;
    private BigDecimal bondAmount;
    private BigDecimal rspRolloverAmount;
    private BigDecimal respRolloverAmount;
    private String rdspTransactionTypeCode;
    private String bondPaymentDate;
    private String grantPaymentDate;
    private BigDecimal totalRolloverAmount; 
    

    private RdspNotionalTransaction associatedGrant;

    public NotionalLotActivityBalancesDto() {
    }

    public BigDecimal getContributionAmount() {
        return contributionAmount;
    }

    public void setContributionAmount(BigDecimal contributionAmount) {
        this.contributionAmount = contributionAmount;
    }

    public BigDecimal getGrantAmount() {
        return grantAmount;
    }

    public void setGrantAmount(BigDecimal grantAmount) {
        this.grantAmount = grantAmount;
    }

    public BigDecimal getBondAmount() {
        return bondAmount;
    }

    public void setBondAmount(BigDecimal bondAmount) {
        this.bondAmount = bondAmount;
    }

    public RdspNotionalTransaction getAssociatedGrant() {
        return associatedGrant;
    }

    public void setAssociatedGrant(RdspNotionalTransaction associatedGrant) {
        this.associatedGrant = associatedGrant;
    }

	public BigDecimal getRspRolloverAmount() {
		return rspRolloverAmount;
	}

	public void setRspRolloverAmount(BigDecimal rspRolloverAmount) {
		this.rspRolloverAmount = rspRolloverAmount;
	}

	public BigDecimal getRespRolloverAmount() {
		return respRolloverAmount;
	}

	public void setRespRolloverAmount(BigDecimal respRolloverAmount) {
		this.respRolloverAmount = respRolloverAmount;
	}

	public BigDecimal getTotalRolloverAmount() {
		return totalRolloverAmount;
	}

	public void setTotalRolloverAmount(BigDecimal totalRolloverAmount) {
		this.totalRolloverAmount = totalRolloverAmount;
	}

	public String getRdspTransactionTypeCode() {
		return rdspTransactionTypeCode;
	}

	public void setRdspTransactionTypeCode(String rdspTransactionTypeCode) {
		this.rdspTransactionTypeCode = rdspTransactionTypeCode;
	}

	public String getBondPaymentDate() {
		return bondPaymentDate;
	}

	public void setBondPaymentDate(String bondPaymentDate) {
		this.bondPaymentDate = bondPaymentDate;
	}

	public String getGrantPaymentDate() {
		return grantPaymentDate;
	}

	public void setGrantPaymentDate(String grantPaymentDate) {
		this.grantPaymentDate = grantPaymentDate;
	}

    
   

}
