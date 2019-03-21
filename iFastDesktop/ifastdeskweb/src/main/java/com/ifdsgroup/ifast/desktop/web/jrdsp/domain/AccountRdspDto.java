package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import com.fasterxml.jackson.annotation.JsonInclude;

import java.util.List;
import java.util.Objects;

@JsonInclude(JsonInclude.Include.NON_NULL)
public class AccountRdspDto {
    private long accountNumber;
    private String closureReasonCode;
    private String accountUuid;
    private String accountStatus;
    private String dtcStatusCode;
    private String sdspStatusCode;
    private String dtcElectionStatusCode;
    private Boolean isTransferredAccount;
    private Boolean isGrant;
    private Boolean isBond;
    private String closureDate;
    private String registrationStatusCode;
    private String specifiedYearStatusCode;
    private Boolean isReportToESDC;
    private String inceptionDate;
    private String grantDate;   
	private String createdBy;
	private String cycleDate;
    private List<AccountElectionHistoryDto> accountElectionHistories;
    private List<AccountElectionHistoryDto> dtcEligibilityHistories;
    private List<GrantBondPaymentHistoryDto> accountGrantBondPaymentHistories;
    public List<AccountElectionHistoryDto> getDtcEligibilityHistories() {
		return dtcEligibilityHistories;
	}

	public void setDtcEligibilityHistories(List<AccountElectionHistoryDto> dtcEligibilityHistories) {
		this.dtcEligibilityHistories = dtcEligibilityHistories;
	}

	public long getAccountNumber() {
        return accountNumber;
    }

    public void setAccountNumber(long accountNumber) {
        this.accountNumber = accountNumber;
    }

    public String getClosureReasonCode() {
        return closureReasonCode;
    }

    public void setClosureReasonCode(String closureReasonCode) {
        this.closureReasonCode = closureReasonCode;
    }

    public String getAccountUuid() {
        return accountUuid;
    }

    public void setAccountUuid(String accountUuid) {
        this.accountUuid = accountUuid;
    }

    public String getAccountStatus() {
        return accountStatus;
    }

    public void setAccountStatus(String accountStatus) {
        this.accountStatus = accountStatus;
    }

    public String getDtcStatusCode() {
        return dtcStatusCode;
    }

    public void setDtcStatusCode(String dtcStatusCode) {
        this.dtcStatusCode = dtcStatusCode;
    }

    public String getSdspStatusCode() {
        return sdspStatusCode;
    }

    public void setSdspStatusCode(String sdspStatusCode) {
        this.sdspStatusCode = sdspStatusCode;
    }

    public String getDtcElectionStatusCode() {
        return dtcElectionStatusCode;
    }

    public void setDtcElectionStatusCode(String dtcElectionStatusCode) {
        this.dtcElectionStatusCode = dtcElectionStatusCode;
    }

    public Boolean getTransferredAccount() {
        return isTransferredAccount;
    }

    public void setTransferredAccount(Boolean transferredAccount) {
        isTransferredAccount = transferredAccount;
    }

    public Boolean getGrant() {
        return isGrant;
    }

    public void setGrant(Boolean grant) {
        isGrant = grant;
    }

    public Boolean getBond() {
        return isBond;
    }

    public void setBond(Boolean bond) {
        isBond = bond;
    }

    public String getClosureDate() {
        return closureDate;
    }

    public void setClosureDate(String closureDate) {
        this.closureDate = closureDate;
    }

    public String getRegistrationStatusCode() {
        return registrationStatusCode;
    }

    public void setRegistrationStatusCode(String registrationStatusCode) {
        this.registrationStatusCode = registrationStatusCode;
    }

    public String getSpecifiedYearStatusCode() {
        return specifiedYearStatusCode;
    }

    public void setSpecifiedYearStatusCode(String specifiedYearStatusCode) {
        this.specifiedYearStatusCode = specifiedYearStatusCode;
    }

    public Boolean getReportToESDC() {
        return isReportToESDC;
    }

    public void setReportToESDC(Boolean reportToESDC) {
        isReportToESDC = reportToESDC;
    }

    public String getInceptionDate() {
        return inceptionDate;
    }

    public void setInceptionDate(String inceptionDate) {
        this.inceptionDate = inceptionDate;
    }

    public String getCreatedBy() {
        return createdBy;
    }

    public void setCreatedBy(String createdBy) {
        this.createdBy = createdBy;
    }

    public List<AccountElectionHistoryDto> getAccountElectionHistories() {
        return accountElectionHistories;
    }

    public void setAccountElectionHistories(List<AccountElectionHistoryDto> accountElectionHistories) {
        this.accountElectionHistories = accountElectionHistories;
    }
	
    public String getGrantDate() {
		return grantDate;
	}

	public void setGrantDate(String grantDate) {
		this.grantDate = grantDate;
	}
	
    public List<GrantBondPaymentHistoryDto> getAccountGrantBondPaymentHistories() {
        return accountGrantBondPaymentHistories;
    }

    public void setAccountGrantBondPaymentHistories(List<GrantBondPaymentHistoryDto> accountGrantBondPaymentHistories) {
        this.accountGrantBondPaymentHistories = accountGrantBondPaymentHistories;
    }
	
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        AccountRdspDto that = (AccountRdspDto) o;
        return accountNumber == that.accountNumber &&
            Objects.equals(closureReasonCode, that.closureReasonCode) &&
            Objects.equals(accountUuid, that.accountUuid) &&
            Objects.equals(accountStatus, that.accountStatus) &&
            Objects.equals(dtcStatusCode, that.dtcStatusCode) &&
            Objects.equals(sdspStatusCode, that.sdspStatusCode) &&
            Objects.equals(dtcElectionStatusCode, that.dtcElectionStatusCode) &&
            Objects.equals(isTransferredAccount, that.isTransferredAccount) &&
            Objects.equals(isGrant, that.isGrant) &&
            Objects.equals(isBond, that.isBond) &&
            Objects.equals(closureDate, that.closureDate) &&
            Objects.equals(registrationStatusCode, that.registrationStatusCode) &&
            Objects.equals(specifiedYearStatusCode, that.specifiedYearStatusCode) &&
            Objects.equals(isReportToESDC, that.isReportToESDC) &&
            Objects.equals(inceptionDate, that.inceptionDate) &&
            Objects.equals(createdBy, that.createdBy) &&
            Objects.equals(grantDate, that.grantDate) &&
            Objects.equals(accountElectionHistories, that.accountElectionHistories)&&
            Objects.equals(accountGrantBondPaymentHistories, that.accountGrantBondPaymentHistories);
    }

    @Override
    public int hashCode() {

        return Objects.hash(accountNumber, closureReasonCode, accountUuid, accountStatus, dtcStatusCode, sdspStatusCode, dtcElectionStatusCode, isTransferredAccount, isGrant, isBond, closureDate, registrationStatusCode, specifiedYearStatusCode, isReportToESDC, inceptionDate, createdBy, accountElectionHistories, grantDate, accountGrantBondPaymentHistories);
    }

    @Override
    public String toString() {
        return "AccountRdspDto{" +
            "\naccountNumber=" + accountNumber +
            "\n, closureReasonCode='" + closureReasonCode + '\'' +
            "\n, accountUuid='" + accountUuid + '\'' +
            "\n, accountStatus='" + accountStatus + '\'' +
            "\n, dtcStatusCode='" + dtcStatusCode + '\'' +
            "\n, sdspStatusCode='" + sdspStatusCode + '\'' +
            "\n, dtcElectionStatusCode='" + dtcElectionStatusCode + '\'' +
            "\n, isTransferredAccount=" + isTransferredAccount +
            "\n, isGrant=" + isGrant +
            "\n, isBond=" + isBond +
            "\n, closureDate='" + closureDate + '\'' +
            "\n, registrationStatusCode='" + registrationStatusCode + '\'' +
            "\n, specifiedYearStatusCode='" + specifiedYearStatusCode + '\'' +
            "\n, isReportToESDC=" + isReportToESDC +
            "\n, inceptionDate='" + inceptionDate + '\'' +
            "\n, createdBy='" + createdBy + '\'' +
            "\n, grantDate='" + grantDate + '\'' +
            "\n, accountElectionHistories=" + accountElectionHistories +
            "\n, accountGrantBondPaymentHistories=" + accountGrantBondPaymentHistories +
        '}';
    }
}
