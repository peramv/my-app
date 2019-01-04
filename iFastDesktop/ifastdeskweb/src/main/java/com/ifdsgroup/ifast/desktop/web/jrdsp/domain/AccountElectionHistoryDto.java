package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import java.util.Objects;

public class AccountElectionHistoryDto {
    private long id;
    private String uuid;
    private long accountNumber;
    private String electionTypeCode;
    private String electionStatusCode;
    private String certificationDate;
    private String transactionDate;
    private String reportingStatusCode;
    private String periodStartDate;
    private String periodEndDate;
    private String effectiveDate;
    private String status;

    public long getId() {
        return id;
    }

    public void setId(long id) {

        this.id = id;
    }

    public String getUuid() {
        return uuid;
    }

    public void setUuid(String uuid) {
        this.uuid = uuid;
    }

    public String getEffectiveDate() {
        return effectiveDate;
    }

    public void setEffectiveDate(String effectiveDate) {
        this.effectiveDate = effectiveDate;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public long getAccountNumber() {
        return accountNumber;
    }

    public void setAccountNumber(long accountNumber) {
        this.accountNumber = accountNumber;
    }

    public String getElectionTypeCode() {
        return electionTypeCode;
    }

    public void setElectionTypeCode(String electionTypeCode) {
        this.electionTypeCode = electionTypeCode;
    }

    public String getElectionStatusCode() {
        return electionStatusCode;
    }

    public void setElectionStatusCode(String electionStatusCode) {
        this.electionStatusCode = electionStatusCode;
    }

    public String getCertificationDate() {
        return certificationDate;
    }

    public void setCertificationDate(String certificationDate) {
        this.certificationDate = certificationDate;
    }

    public String getTransactionDate() {
        return transactionDate;
    }

    public void setTransactionDate(String transactionDate) {
        this.transactionDate = transactionDate;
    }

    public String getReportingStatusCode() {
        return reportingStatusCode;
    }

    public void setReportingStatusCode(String reportingStatusCode) {
        this.reportingStatusCode = reportingStatusCode;
    }

    public String getPeriodStartDate() {
        return periodStartDate;
    }

    public void setPeriodStartDate(String periodStartDate) {
        this.periodStartDate = periodStartDate;
    }

    public String getPeriodEndDate() {
        return periodEndDate;
    }

    public void setPeriodEndDate(String periodEndDate) {
        this.periodEndDate = periodEndDate;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        AccountElectionHistoryDto that = (AccountElectionHistoryDto) o;
        return id == that.id &&
            accountNumber == that.accountNumber &&
            Objects.equals(uuid, that.uuid) &&
            Objects.equals(electionTypeCode, that.electionTypeCode) &&
            Objects.equals(electionStatusCode, that.electionStatusCode) &&
            Objects.equals(certificationDate, that.certificationDate) &&
            Objects.equals(transactionDate, that.transactionDate) &&
            Objects.equals(reportingStatusCode, that.reportingStatusCode) &&
            Objects.equals(periodStartDate, that.periodStartDate) &&
            Objects.equals(periodEndDate, that.periodEndDate) &&
            Objects.equals(effectiveDate, that.effectiveDate) &&
            Objects.equals(status, that.status);
    }

    @Override
    public int hashCode() {

        return Objects.hash(id, uuid, accountNumber, electionTypeCode, electionStatusCode, certificationDate, transactionDate, reportingStatusCode, periodStartDate, periodEndDate, effectiveDate, status);
    }

    @Override
    public String toString() {
        return "AccountElectionHistoryDto{" +
            "\nid=" + id +
            "\n, uuid='" + uuid + '\'' +
            "\n, accountNumber=" + accountNumber +
            "\n, electionTypeCode='" + electionTypeCode + '\'' +
            "\n, electionStatusCode='" + electionStatusCode + '\'' +
            "\n, certificationDate='" + certificationDate + '\'' +
            "\n, transactionDate='" + transactionDate + '\'' +
            "\n, reportingStatusCode='" + reportingStatusCode + '\'' +
            "\n, periodStartDate='" + periodStartDate + '\'' +
            "\n, periodEndDate='" + periodEndDate + '\'' +
            "\n, effectiveDate='" + effectiveDate + '\'' +
            "\n, status='" + status + '\'' +
            '}';
    }
}
