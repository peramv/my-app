package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import java.util.List;

import javax.xml.bind.annotation.XmlRootElement;

import org.springframework.validation.annotation.Validated;

import com.fasterxml.jackson.annotation.JsonInclude;

@XmlRootElement(name="TransactionGetResponse")
public class TransactionGetResponse extends BaseResponse{

	private List<TransactionGetResponseDto> transactions;

	public List<TransactionGetResponseDto> getTransactions() {
		return transactions;
	}

	public void setTransactions(List<TransactionGetResponseDto> transactions) {
		this.transactions = transactions;
	}
	
}
