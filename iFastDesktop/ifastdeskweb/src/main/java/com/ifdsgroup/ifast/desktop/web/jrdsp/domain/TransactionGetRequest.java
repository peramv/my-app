package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.springframework.format.annotation.DateTimeFormat;

import com.fasterxml.jackson.annotation.JsonFormat;

public class TransactionGetRequest {
	
    private String accountNumber;
    private String transactionNumber;
    private String notionalCategory;
    private String transactionType;
    private String description;
    private String fromDate;
    private String toDate;
    
	public TransactionGetRequest() {
		super();
	}

	public TransactionGetRequest(String accountNum, String transactionNumber2, String notionalCategory,
			String transactionType, String description, String fromDate, String toDate) {
		super();
		this.accountNumber = accountNum;
		this.transactionNumber =  transactionNumber2;
		this.notionalCategory = notionalCategory;
		this.transactionType = transactionType;
		this.description = description;
		this.fromDate = fromDate;
		this.toDate = toDate;
	}

	public String getNotionalCategory() {
		return notionalCategory;
	}

	public void setNotionalCategory(String notionalCategory) {
		this.notionalCategory = notionalCategory;
	}

	public String getTransactionType() {
		return transactionType;
	}

	public void setTransactionType(String transactionType) {
		this.transactionType = transactionType;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}



	



	
	
	public String getAccountNumber() {
		return accountNumber;
	}

	public void setAccountNumber(String accountNumber) {
		this.accountNumber = accountNumber;
	}

	public String getTransactionNumber() {
		return transactionNumber;
	}

	public void setTransactionNumber(String transactionNumber) {
		this.transactionNumber = transactionNumber;
	}

	public String getFromDate() {
		return fromDate;
	}

	public void setFromDate(String fromDate) {
		this.fromDate = fromDate;
	}

	public String getToDate() {
		return toDate;
	}

	public void setToDate(String toDate) {
		this.toDate = toDate;
	}

	
    


}
