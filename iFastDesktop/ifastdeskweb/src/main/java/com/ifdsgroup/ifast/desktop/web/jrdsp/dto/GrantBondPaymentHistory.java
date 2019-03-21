package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import com.fasterxml.jackson.annotation.JsonInclude;

@JsonInclude(JsonInclude.Include.NON_NULL)	
public class GrantBondPaymentHistory {
	    private String accountNumber;
	    private String paymentTypeCode;
	    private String reportingStatusCode;
	    private String effectiveFromDate;
	    private String effectiveToDate;
	    private String status;
	    private String lastNoGrant;
	    
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
		public String getLastNoGrant() {
			return lastNoGrant;
		}
		public void setLastNoGrant(String lastNoGrant) {
			this.lastNoGrant = lastNoGrant;
		}

	    
}
