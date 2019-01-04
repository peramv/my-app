package com.ifdsgroup.ifast.desktop.web.jrdsp.domain;

import java.util.List;

import javax.xml.bind.annotation.XmlRootElement;

import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.RdspTransactions;
import com.ifdsgroup.ifast.desktop.web.jrdsp.dto.AccountResponse;


@XmlRootElement(name="NotionalActivityDto")
public class NotionalActivityDto {
	
	private String beneficiaryName;
	
	private List<RdspTransactions> transactions;
	
	  public String getBeneficiaryName() {
               return beneficiaryName;
        }

     public void setBeneficiaryName(String beneficiaryName) {
                this.beneficiaryName = beneficiaryName;
	       }

	public List<RdspTransactions> getTransactions() {
		return transactions;
	}

	public void setTransactions(List<RdspTransactions> transactions) {
		this.transactions = transactions;
	}
	
}
