package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import java.util.Date;
import java.util.Objects;

import org.springframework.validation.annotation.Validated;

import com.fasterxml.jackson.annotation.JsonInclude;

@Validated
@JsonInclude(JsonInclude.Include.NON_NULL)
public class GrantBondPaymentHistoryDto {
    private String id;
    private String accountNumber;
    private String paymentTypeCode;
    private String reportingStatusCode;
    private String effectiveFromDate;
    private String effectiveToDate;
    private String status;
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public String getAccountNumber() {
		return accountNumber;
	}
	public void setAccountNumber(String accountNumber) {
		this.accountNumber = accountNumber;
	}
	public String getPaymentTypeCode() {
		return paymentTypeCode;
	}
	public void setPaymentTypeCode(String paymentTypeCode) {
		this.paymentTypeCode = paymentTypeCode;
	}
	public String getReportingStatusCode() {
		return reportingStatusCode;
	}
	public void setReportingStatusCode(String reportingStatusCode) {
		this.reportingStatusCode = reportingStatusCode;
	}
	public String getEffectiveFromDate() {
		return effectiveFromDate;
	}
	public void setEffectiveFromDate(String effectiveFromDate) {
		this.effectiveFromDate = effectiveFromDate;
	}
	public String getEffectiveToDate() {
		return effectiveToDate;
	}
	public void setEffectiveToDate(String effectiveToDate) {
		this.effectiveToDate = effectiveToDate;
	}
	public String getStatus() {
		return status;
	}
	public void setStatus(String status) {
		this.status = status;
	}
	@Override
	public String toString() {
		return "GrantBondPaymentHistoryDto [id=" + id + ", accountNumber=" + accountNumber + ", paymentTypeCode="
				+ paymentTypeCode + ", reportingStatusCode=" + reportingStatusCode + ", effectiveFromDate="
				+ effectiveFromDate + ", effectiveToDate=" + effectiveToDate + ", status=" + status + "]";
	}

    
}
