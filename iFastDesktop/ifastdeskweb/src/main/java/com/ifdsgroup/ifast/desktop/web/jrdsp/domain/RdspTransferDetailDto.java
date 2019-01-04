package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;
import java.math.BigDecimal;
import java.util.function.Consumer;
import java.util.Objects;

public class RdspTransferDetailDto {

    private String externalContractNumber;
    private String externalSpecimenPlanNumber;
    private BigDecimal openingFmv;
    private BigDecimal yearEndCdsaAmount;
    private BigDecimal yearEndContributionsAmount;
    private BigDecimal priorYearRedemptionTaxableAmount;
    private BigDecimal priorYearRedemptionNonTaxableAmount;
    private BigDecimal currentYearRedemptionTaxableAmount;
    private BigDecimal currentYearRedemptionNonTaxableAmount;
    private String contractNumber;
    private String specimenPlanNumber;
    private BigDecimal rolloverAmount;
    private BigDecimal grantAmount;
    private BigDecimal bondAmount;
    private BigDecimal totalPayments;
    private String transactionId;
    private String accountNumber;
    private Boolean esdcSent;
    private Boolean esdcResponse;
    private Boolean moneyOutTrade;
    private String transferInStatusTypeCode;
    private String transactionStatusCode;
    private String cdspRegStatus;

    public RdspTransferDetailDto() {
    }

    public RdspTransferDetailDto(Consumer<RdspTransferDetailDto> builder) {
        builder.accept(this);
    }


    public String getExternalContractNumber() {
        return externalContractNumber;
    }

    public void setExternalContractNumber(String externalContractNumber) {
        this.externalContractNumber = externalContractNumber;
    }

    public String getExternalSpecimenPlanNumber() {
        return externalSpecimenPlanNumber;
    }

    public void setExternalSpecimenPlanNumber(String externalSpecimenPlanNumber) {
        this.externalSpecimenPlanNumber = externalSpecimenPlanNumber;
    }

    public BigDecimal getOpeningFmv() {
        return openingFmv;
    }

    public void setOpeningFmv(BigDecimal openingFmv) {
        this.openingFmv = openingFmv;
    }

    public BigDecimal getYearEndCdsaAmount() {
        return yearEndCdsaAmount;
    }

    public void setYearEndCdsaAmount(BigDecimal yearEndCdsaAmount) {
        this.yearEndCdsaAmount = yearEndCdsaAmount;
    }

    public BigDecimal getYearEndContributionsAmount() {
        return yearEndContributionsAmount;
    }

    public void setYearEndContributionsAmount(BigDecimal yearEndContributionsAmount) {
        this.yearEndContributionsAmount = yearEndContributionsAmount;
    }

    public BigDecimal getPriorYearRedemptionTaxableAmount() {
        return priorYearRedemptionTaxableAmount;
    }

    public void setPriorYearRedemptionTaxableAmount(BigDecimal priorYearRedemptionTaxableAmount) {
        this.priorYearRedemptionTaxableAmount = priorYearRedemptionTaxableAmount;
    }

    public BigDecimal getPriorYearRedemptionNonTaxableAmount() {
        return priorYearRedemptionNonTaxableAmount;
    }

    public void setPriorYearRedemptionNonTaxableAmount(BigDecimal priorYearRedemptionNonTaxableAmount) {
        this.priorYearRedemptionNonTaxableAmount = priorYearRedemptionNonTaxableAmount;
    }

    public BigDecimal getCurrentYearRedemptionTaxableAmount() {
        return currentYearRedemptionTaxableAmount;
    }

    public void setCurrentYearRedemptionTaxableAmount(BigDecimal currentYearRedemptionTaxableAmount) {
        this.currentYearRedemptionTaxableAmount = currentYearRedemptionTaxableAmount;
    }

    public BigDecimal getCurrentYearRedemptionNonTaxableAmount() {
        return currentYearRedemptionNonTaxableAmount;
    }

    public void setCurrentYearRedemptionNonTaxableAmount(BigDecimal currentYearRedemptionNonTaxableAmount) {
        this.currentYearRedemptionNonTaxableAmount = currentYearRedemptionNonTaxableAmount;
    }

    public String getContractNumber() {
        return contractNumber;
    }

    public void setContractNumber(String contractNumber) {
        this.contractNumber = contractNumber;
    }

    public String getSpecimenPlanNumber() {
        return specimenPlanNumber;
    }

    public void setSpecimenPlanNumber(String specimenPlanNumber) {
        this.specimenPlanNumber = specimenPlanNumber;
    }

    public BigDecimal getRolloverAmount() {
        return rolloverAmount;
    }

    public void setRolloverAmount(BigDecimal rolloverAmount) {
        this.rolloverAmount = rolloverAmount;
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

    public BigDecimal getTotalPayments() {
        return totalPayments;
    }

    public void setTotalPayments(BigDecimal totalPayments) {
        this.totalPayments = totalPayments;
    }

    public String getTransactionId() {
        return transactionId;
    }

    public void setTransactionId(String transactionId) {
        this.transactionId = transactionId;
    }

    public String getAccountNumber() {
        return accountNumber;
    }

    public void setAccountNumber(String accountNumber) {
        this.accountNumber = accountNumber;
    }

    public Boolean getEsdcSent() {
        return esdcSent;
    }

    public void setEsdcSent(Boolean esdcSent) {
        this.esdcSent = esdcSent;
    }

    public Boolean getEsdcResponse() {
        return esdcResponse;
    }

    public void setEsdcResponse(Boolean esdcResponse) {
        this.esdcResponse = esdcResponse;
    }

    public Boolean getMoneyOutTrade() {
        return moneyOutTrade;
    }

    public void setMoneyOutTrade(Boolean moneyOutTrade) {
        this.moneyOutTrade = moneyOutTrade;
    }

    public String getTransferInStatusTypeCode() {
        return transferInStatusTypeCode;
    }

    public void setTransferInStatusTypeCode(String transferInStatusTypeCode) {
        this.transferInStatusTypeCode = transferInStatusTypeCode;
    }
    
    public String getTransactionStatusCode() {
        return transactionStatusCode;
    }

    public void setTransactionStatusCode(String transactionStatusCode) {
        this.transactionStatusCode = transactionStatusCode;
    }
    
	public String getCdspRegStatus() {
		return cdspRegStatus;
	}

	public void setCdspRegStatus(String cdspRegStatus) {
		this.cdspRegStatus = cdspRegStatus;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((accountNumber == null) ? 0 : accountNumber.hashCode());
		result = prime * result + ((bondAmount == null) ? 0 : bondAmount.hashCode());
		result = prime * result + ((cdspRegStatus == null) ? 0 : cdspRegStatus.hashCode());
		result = prime * result + ((contractNumber == null) ? 0 : contractNumber.hashCode());
		result = prime * result + ((currentYearRedemptionNonTaxableAmount == null) ? 0
				: currentYearRedemptionNonTaxableAmount.hashCode());
		result = prime * result
				+ ((currentYearRedemptionTaxableAmount == null) ? 0 : currentYearRedemptionTaxableAmount.hashCode());
		result = prime * result + ((esdcResponse == null) ? 0 : esdcResponse.hashCode());
		result = prime * result + ((esdcSent == null) ? 0 : esdcSent.hashCode());
		result = prime * result + ((externalContractNumber == null) ? 0 : externalContractNumber.hashCode());
		result = prime * result + ((externalSpecimenPlanNumber == null) ? 0 : externalSpecimenPlanNumber.hashCode());
		result = prime * result + ((grantAmount == null) ? 0 : grantAmount.hashCode());
		result = prime * result + ((moneyOutTrade == null) ? 0 : moneyOutTrade.hashCode());
		result = prime * result + ((openingFmv == null) ? 0 : openingFmv.hashCode());
		result = prime * result
				+ ((priorYearRedemptionNonTaxableAmount == null) ? 0 : priorYearRedemptionNonTaxableAmount.hashCode());
		result = prime * result
				+ ((priorYearRedemptionTaxableAmount == null) ? 0 : priorYearRedemptionTaxableAmount.hashCode());
		result = prime * result + ((rolloverAmount == null) ? 0 : rolloverAmount.hashCode());
		result = prime * result + ((specimenPlanNumber == null) ? 0 : specimenPlanNumber.hashCode());
		result = prime * result + ((totalPayments == null) ? 0 : totalPayments.hashCode());
		result = prime * result + ((transactionId == null) ? 0 : transactionId.hashCode());
		result = prime * result + ((transactionStatusCode == null) ? 0 : transactionStatusCode.hashCode());
		result = prime * result + ((transferInStatusTypeCode == null) ? 0 : transferInStatusTypeCode.hashCode());
		result = prime * result + ((yearEndCdsaAmount == null) ? 0 : yearEndCdsaAmount.hashCode());
		result = prime * result + ((yearEndContributionsAmount == null) ? 0 : yearEndContributionsAmount.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		RdspTransferDetailDto other = (RdspTransferDetailDto) obj;
		if (accountNumber == null) {
			if (other.accountNumber != null)
				return false;
		} else if (!accountNumber.equals(other.accountNumber))
			return false;
		if (bondAmount == null) {
			if (other.bondAmount != null)
				return false;
		} else if (!bondAmount.equals(other.bondAmount))
			return false;
		if (cdspRegStatus == null) {
			if (other.cdspRegStatus != null)
				return false;
		} else if (!cdspRegStatus.equals(other.cdspRegStatus))
			return false;
		if (contractNumber == null) {
			if (other.contractNumber != null)
				return false;
		} else if (!contractNumber.equals(other.contractNumber))
			return false;
		if (currentYearRedemptionNonTaxableAmount == null) {
			if (other.currentYearRedemptionNonTaxableAmount != null)
				return false;
		} else if (!currentYearRedemptionNonTaxableAmount.equals(other.currentYearRedemptionNonTaxableAmount))
			return false;
		if (currentYearRedemptionTaxableAmount == null) {
			if (other.currentYearRedemptionTaxableAmount != null)
				return false;
		} else if (!currentYearRedemptionTaxableAmount.equals(other.currentYearRedemptionTaxableAmount))
			return false;
		if (esdcResponse == null) {
			if (other.esdcResponse != null)
				return false;
		} else if (!esdcResponse.equals(other.esdcResponse))
			return false;
		if (esdcSent == null) {
			if (other.esdcSent != null)
				return false;
		} else if (!esdcSent.equals(other.esdcSent))
			return false;
		if (externalContractNumber == null) {
			if (other.externalContractNumber != null)
				return false;
		} else if (!externalContractNumber.equals(other.externalContractNumber))
			return false;
		if (externalSpecimenPlanNumber == null) {
			if (other.externalSpecimenPlanNumber != null)
				return false;
		} else if (!externalSpecimenPlanNumber.equals(other.externalSpecimenPlanNumber))
			return false;
		if (grantAmount == null) {
			if (other.grantAmount != null)
				return false;
		} else if (!grantAmount.equals(other.grantAmount))
			return false;
		if (moneyOutTrade == null) {
			if (other.moneyOutTrade != null)
				return false;
		} else if (!moneyOutTrade.equals(other.moneyOutTrade))
			return false;
		if (openingFmv == null) {
			if (other.openingFmv != null)
				return false;
		} else if (!openingFmv.equals(other.openingFmv))
			return false;
		if (priorYearRedemptionNonTaxableAmount == null) {
			if (other.priorYearRedemptionNonTaxableAmount != null)
				return false;
		} else if (!priorYearRedemptionNonTaxableAmount.equals(other.priorYearRedemptionNonTaxableAmount))
			return false;
		if (priorYearRedemptionTaxableAmount == null) {
			if (other.priorYearRedemptionTaxableAmount != null)
				return false;
		} else if (!priorYearRedemptionTaxableAmount.equals(other.priorYearRedemptionTaxableAmount))
			return false;
		if (rolloverAmount == null) {
			if (other.rolloverAmount != null)
				return false;
		} else if (!rolloverAmount.equals(other.rolloverAmount))
			return false;
		if (specimenPlanNumber == null) {
			if (other.specimenPlanNumber != null)
				return false;
		} else if (!specimenPlanNumber.equals(other.specimenPlanNumber))
			return false;
		if (totalPayments == null) {
			if (other.totalPayments != null)
				return false;
		} else if (!totalPayments.equals(other.totalPayments))
			return false;
		if (transactionId == null) {
			if (other.transactionId != null)
				return false;
		} else if (!transactionId.equals(other.transactionId))
			return false;
		if (transactionStatusCode == null) {
			if (other.transactionStatusCode != null)
				return false;
		} else if (!transactionStatusCode.equals(other.transactionStatusCode))
			return false;
		if (transferInStatusTypeCode == null) {
			if (other.transferInStatusTypeCode != null)
				return false;
		} else if (!transferInStatusTypeCode.equals(other.transferInStatusTypeCode))
			return false;
		if (yearEndCdsaAmount == null) {
			if (other.yearEndCdsaAmount != null)
				return false;
		} else if (!yearEndCdsaAmount.equals(other.yearEndCdsaAmount))
			return false;
		if (yearEndContributionsAmount == null) {
			if (other.yearEndContributionsAmount != null)
				return false;
		} else if (!yearEndContributionsAmount.equals(other.yearEndContributionsAmount))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "RdspTransferDetailDto [externalContractNumber=" + externalContractNumber
				+ ", externalSpecimenPlanNumber=" + externalSpecimenPlanNumber + ", openingFmv=" + openingFmv
				+ ", yearEndCdsaAmount=" + yearEndCdsaAmount + ", yearEndContributionsAmount="
				+ yearEndContributionsAmount + ", priorYearRedemptionTaxableAmount=" + priorYearRedemptionTaxableAmount
				+ ", priorYearRedemptionNonTaxableAmount=" + priorYearRedemptionNonTaxableAmount
				+ ", currentYearRedemptionTaxableAmount=" + currentYearRedemptionTaxableAmount
				+ ", currentYearRedemptionNonTaxableAmount=" + currentYearRedemptionNonTaxableAmount
				+ ", contractNumber=" + contractNumber + ", specimenPlanNumber=" + specimenPlanNumber
				+ ", rolloverAmount=" + rolloverAmount + ", grantAmount=" + grantAmount + ", bondAmount=" + bondAmount
				+ ", totalPayments=" + totalPayments + ", transactionId=" + transactionId + ", accountNumber="
				+ accountNumber + ", esdcSent=" + esdcSent + ", esdcResponse=" + esdcResponse + ", moneyOutTrade="
				+ moneyOutTrade + ", transferInStatusTypeCode=" + transferInStatusTypeCode + ", transactionStatusCode="
				+ transactionStatusCode + ", cdspRegStatus=" + cdspRegStatus + "]";
	}


    
   

}
