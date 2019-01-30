package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="notionalLotActivityDetailsRequest")
public class NotionalLotActivityDetailsRequest {

		private String accountNumber;
		private String notionalCategory;
	    private String transactionType;
	    private String fromDate;
	    private String toDate;
	    private String transactionNumber;
	    private String lotId;
	    private String start;
	    private String count;

	    public NotionalLotActivityDetailsRequest() {
	    	
	    }


		public NotionalLotActivityDetailsRequest(String accountNumber, String notionalCategory, String transactionType,
				String fromDate, String toDate, String transactionNumber, String lotId, String start, String count) {
			super();
			this.accountNumber = accountNumber;
			this.notionalCategory = notionalCategory;
			this.transactionType = transactionType;
			this.fromDate = fromDate;
			this.toDate = toDate;
			this.transactionNumber = transactionNumber;
			this.lotId = lotId;
			this.start = start;
			this.count = count;
		}


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

	    public String getTransactionNumber() {
	        return transactionNumber;
	    }

	    public void setTransactionNumber(String transactionNumber) {
	        this.transactionNumber = transactionNumber;
	    }

	    public String getLotId() {
	        return lotId;
	    }

	    public void setLotId(String lotId) {
	        this.lotId = lotId;
	    }

	    public String getStart() {
			return start;
		}


		public void setStart(String start) {
			this.start = start;
		}


		public String getCount() {
			return count;
		}


		public void setCount(String count) {
			this.count = count;
		}


		@Override
		public boolean equals(Object obj) {
			if (this == obj)
				return true;
			if (obj == null)
				return false;
			if (getClass() != obj.getClass())
				return false;
			NotionalLotActivityDetailsRequest other = (NotionalLotActivityDetailsRequest) obj;
			if (accountNumber == null) {
				if (other.accountNumber != null)
					return false;
			} else if (!accountNumber.equals(other.accountNumber))
				return false;
			if (count == null) {
				if (other.count != null)
					return false;
			} else if (!count.equals(other.count))
				return false;
			if (fromDate == null) {
				if (other.fromDate != null)
					return false;
			} else if (!fromDate.equals(other.fromDate))
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
			if (start == null) {
				if (other.start != null)
					return false;
			} else if (!start.equals(other.start))
				return false;
			if (toDate == null) {
				if (other.toDate != null)
					return false;
			} else if (!toDate.equals(other.toDate))
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
		public int hashCode() {
			final int prime = 31;
			int result = 1;
			result = prime * result + ((accountNumber == null) ? 0 : accountNumber.hashCode());
			result = prime * result + ((count == null) ? 0 : count.hashCode());
			result = prime * result + ((fromDate == null) ? 0 : fromDate.hashCode());
			result = prime * result + ((lotId == null) ? 0 : lotId.hashCode());
			result = prime * result + ((notionalCategory == null) ? 0 : notionalCategory.hashCode());
			result = prime * result + ((start == null) ? 0 : start.hashCode());
			result = prime * result + ((toDate == null) ? 0 : toDate.hashCode());
			result = prime * result + ((transactionNumber == null) ? 0 : transactionNumber.hashCode());
			result = prime * result + ((transactionType == null) ? 0 : transactionType.hashCode());
			return result;
		}

	    @Override
		public String toString() {
			return "NotionalLotActivityDetailsRequest [accountNumber=" + accountNumber + ", notionalCategory="
					+ notionalCategory + ", transactionType=" + transactionType + ", fromDate=" + fromDate + ", toDate="
					+ toDate + ", transactionNumber=" + transactionNumber + ", lotId=" + lotId + ", start=" + start
					+ ", count=" + count + "]";
		}

}
