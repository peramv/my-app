package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import java.util.List;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="NotionalLotActivityDetailsResponse")
public class NotionalLotActivityDetailsResponse extends BaseResponse {
	private String inceptionDate;
	private String accountNumber;

    private List<NotionalLotActivityDetailsDto> notionalLotActivityDetails;

    public String getInceptionDate() {
        return inceptionDate;
    }

    public void setInceptionDate(String inceptionDate) {
        this.inceptionDate = inceptionDate;
    }

    public String getAccountNumber() {
		return accountNumber;
	}

	public void setAccountNumber(String accountNumber) {
		this.accountNumber = accountNumber;
	}

	public List<NotionalLotActivityDetailsDto> getNotionalLotActivityDetails() {
        return notionalLotActivityDetails;
    }

    public void setNotionalLotActivityDetails(List<NotionalLotActivityDetailsDto> notionalLotActivityDetails) {
        this.notionalLotActivityDetails = notionalLotActivityDetails;
    }



    @Override
	public String toString() {
		return "NotionalLotActivityDetailsResponse [inceptionDate=" + inceptionDate + ", accountNumber=" + accountNumber
				+ ", notionalLotActivityDetails=" + notionalLotActivityDetails + "]";
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((accountNumber == null) ? 0 : accountNumber.hashCode());
		result = prime * result + ((inceptionDate == null) ? 0 : inceptionDate.hashCode());
		result = prime * result + ((notionalLotActivityDetails == null) ? 0 : notionalLotActivityDetails.hashCode());
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
		NotionalLotActivityDetailsResponse other = (NotionalLotActivityDetailsResponse) obj;
		if (accountNumber == null) {
			if (other.accountNumber != null)
				return false;
		} else if (!accountNumber.equals(other.accountNumber))
			return false;
		if (inceptionDate == null) {
			if (other.inceptionDate != null)
				return false;
		} else if (!inceptionDate.equals(other.inceptionDate))
			return false;
		if (notionalLotActivityDetails == null) {
			if (other.notionalLotActivityDetails != null)
				return false;
		} else if (!notionalLotActivityDetails.equals(other.notionalLotActivityDetails))
			return false;
		return true;
	}


}
