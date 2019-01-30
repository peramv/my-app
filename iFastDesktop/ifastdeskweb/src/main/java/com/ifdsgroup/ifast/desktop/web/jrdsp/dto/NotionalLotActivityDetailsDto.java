package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.math.BigDecimal;
import java.util.Objects;

public class NotionalLotActivityDetailsDto {

    private String accountNumber;
    private String notionalCategory;
    private String transactionType;
    private String transactionNumber;
    private Integer lotId;
    private BigDecimal amount;
    private String tradeDate;
    private String paymentDate;
	public String getAccountNumber() {
		return accountNumber;
	}
	public void setAccountNumber(String accountNumber) {
		this.accountNumber = accountNumber;
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
	public String getTransactionNumber() {
		return transactionNumber;
	}
	public void setTransactionNumber(String transactionNumber) {
		this.transactionNumber = transactionNumber;
	}
	public Integer getLotId() {
		return lotId;
	}
	public void setLotId(Integer lotId) {
		this.lotId = lotId;
	}
	public BigDecimal getAmount() {
		return amount;
	}
	public void setAmount(BigDecimal amount) {
		this.amount = amount;
	}
	public String getTradeDate() {
		return tradeDate;
	}
	public void setTradeDate(String tradeDate) {
		this.tradeDate = tradeDate;
	}
	public String getPaymentDate() {
		return paymentDate;
	}
	public void setPaymentDate(String paymentDate) {
		this.paymentDate = paymentDate;
	}
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((accountNumber == null) ? 0 : accountNumber.hashCode());
		result = prime * result + ((amount == null) ? 0 : amount.hashCode());
		result = prime * result + ((lotId == null) ? 0 : lotId.hashCode());
		result = prime * result + ((notionalCategory == null) ? 0 : notionalCategory.hashCode());
		result = prime * result + ((paymentDate == null) ? 0 : paymentDate.hashCode());
		result = prime * result + ((tradeDate == null) ? 0 : tradeDate.hashCode());
		result = prime * result + ((transactionNumber == null) ? 0 : transactionNumber.hashCode());
		result = prime * result + ((transactionType == null) ? 0 : transactionType.hashCode());
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
		NotionalLotActivityDetailsDto other = (NotionalLotActivityDetailsDto) obj;
		if (accountNumber == null) {
			if (other.accountNumber != null)
				return false;
		} else if (!accountNumber.equals(other.accountNumber))
			return false;
		if (amount == null) {
			if (other.amount != null)
				return false;
		} else if (!amount.equals(other.amount))
			return false;
		if (lotId == null) {
			if (other.lotId != null)
				return false;
		} else if (!lotId.equals(other.lotId))
			return false;
		if (notionalCategory == null) {
			if (other.notionalCategory != null)
				return false;
		} else if (!notionalCategory.equals(other.notionalCategory))
			return false;
		if (paymentDate == null) {
			if (other.paymentDate != null)
				return false;
		} else if (!paymentDate.equals(other.paymentDate))
			return false;
		if (tradeDate == null) {
			if (other.tradeDate != null)
				return false;
		} else if (!tradeDate.equals(other.tradeDate))
			return false;
		if (transactionNumber == null) {
			if (other.transactionNumber != null)
				return false;
		} else if (!transactionNumber.equals(other.transactionNumber))
			return false;
		if (transactionType == null) {
			if (other.transactionType != null)
				return false;
		} else if (!transactionType.equals(other.transactionType))
			return false;
		return true;
	}
	@Override
	public String toString() {
		return "NotionalLotActivityDetailsDto [accountNumber=" + accountNumber + ", notionalCategory="
				+ notionalCategory + ", transactionType=" + transactionType + ", transactionNumber=" + transactionNumber
				+ ", lotId=" + lotId + ", amount=" + amount + ", tradeDate=" + tradeDate + ", paymentDate="
				+ paymentDate + "]";
	}

    
}
