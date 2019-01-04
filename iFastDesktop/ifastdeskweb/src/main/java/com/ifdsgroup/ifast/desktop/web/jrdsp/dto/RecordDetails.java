package com.ifdsgroup.ifast.desktop.web.jrdsp.dto;

import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement(name="RecordDetails")
public class RecordDetails {
	private String holderSinOrBn;
	private String primaryCaregiverSinOrAgencyBn;
	private String city;
	private String issuerBn;
	private String contractCreationOrUpdateDate;
	private String primaryCaregiverSurnameOrAgencyName;
	private String updateDate;
	private String holderSurnameOrHolderAgencyName;
	private String language;
	private String closureReasonDate;
	private String closureDate;
	private String addressLine1;
	private String closureReason;
	private String holderRelationship;
	private String issuerTransactionNumber;
	private String beneficiarySex;
	private String primaryCaregiverName; 	
	private String addressLine3;
	private String addDate;
	private String postalCode;
	private String specimenPlan;
	private String holderDateOfBirth;
	private String otherSpecimenPlan;
	private String holderGivenName;
	private String primaryCaregiverType;
	private String transferIndicator;
	private String transactionType;
	private String addressLine2;
	private String recordType;
	private String beneficiarySurname;
	private String beneficiaryGivenName;
	private String beneficiarySin;
	private String holderSex;
	private String contract;
	private String holderType;
	private String province;
	private String country;
	private String beneficiaryDateOfBirth;
	private String otherContract;
	private String contractSignatureDate;
	private String removalDate;
	private String contributionDate;
	private String primaryCaregiverSin1OrAgencyBn;
	private String bondRequestDate;
	private String grantRequested;
	private String primaryCaregiverSurname1OrAgencyName;
	private String primaryCaregiverType1;
	private String primaryCaregiverType2;
	private String primaryCaregiverGivenName2;
	private String primaryCaregiverSin2OrAgencyBn;
	private String certificationDate;
	private String transactionDate;
	private String primaryCaregiverSurname2OrAgencyName;
	private String primaryCaregiverGivenName1;
	private String contributionAmount;
	private String primaryCaregiverGivenName;
	private String retirementSavingRolloverAmount;
	private String retirementSavingRolloverDate;
	private String transactionOrigin;
	private String originalIssuerBN;
	private String contractNumber;
	private String electionPeriodStartDate;
	private String electionPeriodEndDate;
	private String educationSavingRolloverAmount;
	private String educationSavingRolloverDate;
	private String reportingDate;
	private String fmvAmount;
	private String transactionNumber;
	private String grantAmount;
	private String bondAmount;
	private String dateOfPayment;
	private String refusalReason;
	private String originalIssuerBn;
	private String paymentRequisitioned;
	private String cdspSystemDate;
	private String cdspSystemSin;
	private String addConsentDate;
	private String consentSinOrBn;
	private String consentGivenName;
	private String consentSurnameOrAgencyName;
	private String consentType;
	private String revokeConsentDate;
	private String beneficiaryDtcEligibilityYear;
	private String beneficiaryDtcEligibiltyStatus;
	private String beneficiaryDtcUndeterminedReason;
	private String dapDate;
	private String contributionPortionOfTheNonTaxableFormula;
	private String grantPortionOfTheDap;
	private String bondPortionOfTheDap;
	private String nonTaxablePortionOfTheDap;
	private String totalDapAmount;
	private String dapRetirementSavingsRolloverAmount;
	private String ldapDate;
	private String grantPortionOfTheLdap;
	private String bondPortionOfTheLdap;
	private String nonTaxablePortionOfTheLdap;
	private String totalLdapAmount;
	private String ldapRetirementSavingsRolloverAmount;
	private String repaymentDate;
	private String grantRepaymentAmount;
	private String bondRepaymentAmount;
	private String grantTerminationAdjustmentAmount;
	private String bondterminationAdjustmentAmount;
	private String repaymentReason;
	private String fieldName;
	private String errorCode;
	private String sinIssue;
	private String givenNameIssue;
	private String surnameIssue;
	private String birthDateIssue;
	private String sexIssue;
	private String sin;
	private String originalIssuerTransactionNumber;
	private String stopRequestDate;
	private String currentContractStatus;
	private String contractInformationPassesTransactionValidation;
	private String contractInformationPasses60DayRule;
	private String contractInformationContainsMinimumInformationRequirements;
	private String beneficiarySinPassesIdentityValidationAtSir;
	private String holdersSinPassesIdentityValidationAtSir;
	private String currentContractIsWaitingForATransferToOccur;
	private String beneficiaryPassesResidencyValidationAtContractSignatureDate;
	private String beneficiaryPassesDtcEligibilityValidationAtContractSignatureDate;
	private String beneficiarySinIsUsableAtContractSignatureDate;
	private String holdersSinIsUsableAtContractSignatureDate;
	private String remainingBalanceOnContract;
	private String currentReasonForChangeOfContractStatus;
	private String currentTransferStatus;
	private String currentResidencyEligibilityOfBeneficiary;
	private String currentDtcEligibilityOfBeneficiary;
	private String currentBeneficiarySinUsability;
	private String currentHoldersSinUsability;
	private String contractRegistrationRetirementSavingsRolloverCompliant;
	private String contractRegistrationEducationSavingsRolloverCompliant;
	
	
	

	public String getAddConsentDate() {
		return addConsentDate;
	}
	public void setAddConsentDate(String addConsentDate) {
		this.addConsentDate = addConsentDate;
	}
	public String getConsentSinOrBn() {
		return consentSinOrBn;
	}
	public void setConsentSinOrBn(String consentSinOrBn) {
		this.consentSinOrBn = consentSinOrBn;
	}
	public String getConsentGivenName() {
		return consentGivenName;
	}
	public void setConsentGivenName(String consentGivenName) {
		this.consentGivenName = consentGivenName;
	}
	public String getConsentSurnameOrAgencyName() {
		return consentSurnameOrAgencyName;
	}
	public void setConsentSurnameOrAgencyName(String consentSurnameOrAgencyName) {
		this.consentSurnameOrAgencyName = consentSurnameOrAgencyName;
	}
	public String getConsentType() {
		return consentType;
	}
	public void setConsentType(String consentType) {
		this.consentType = consentType;
	}
	public String getRevokeConsentDate() {
		return revokeConsentDate;
	}
	public void setRevokeConsentDate(String revokeConsentDate) {
		this.revokeConsentDate = revokeConsentDate;
	}
	private String errorCodes;
	
	public String getHolderSinOrBn() {
		return holderSinOrBn;
	}
	public void setHolderSinOrBn(String holderSinOrBn) {
		this.holderSinOrBn = holderSinOrBn;
	}
	public String getPrimaryCaregiverSinOrAgencyBn() {
		return primaryCaregiverSinOrAgencyBn;
	}
	public void setPrimaryCaregiverSinOrAgencyBn(String primaryCaregiverSinOrAgencyBn) {
		this.primaryCaregiverSinOrAgencyBn = primaryCaregiverSinOrAgencyBn;
	}
	public String getCity() {
		return city;
	}
	public void setCity(String city) {
		this.city = city;
	}
	public String getIssuerBn() {
		return issuerBn;
	}
	public void setIssuerBn(String issuerBn) {
		this.issuerBn = issuerBn;
	}
	public String getContractCreationOrUpdateDate() {
		return contractCreationOrUpdateDate;
	}
	public void setContractCreationOrUpdateDate(String contractCreationOrUpdateDate) {
		this.contractCreationOrUpdateDate = contractCreationOrUpdateDate;
	}
	public String getPrimaryCaregiverSurnameOrAgencyName() {
		return primaryCaregiverSurnameOrAgencyName;
	}
	public void setPrimaryCaregiverSurnameOrAgencyName(String primaryCaregiverSurnameOrAgencyName) {
		this.primaryCaregiverSurnameOrAgencyName = primaryCaregiverSurnameOrAgencyName;
	}
	public String getUpdateDate() {
		return updateDate;
	}
	public void setUpdateDate(String updateDate) {
		this.updateDate = updateDate;
	}
	public String getHolderSurnameOrHolderAgencyName() {
		return holderSurnameOrHolderAgencyName;
	}
	public void setHolderSurnameOrHolderAgencyName(String holderSurnameOrHolderAgencyName) {
		this.holderSurnameOrHolderAgencyName = holderSurnameOrHolderAgencyName;
	}
	public String getLanguage() {
		return language;
	}
	public void setLanguage(String language) {
		this.language = language;
	}
	public String getClosureReasonDate() {
		return closureReasonDate;
	}
	public void setClosureReasonDate(String closureReasonDate) {
		this.closureReasonDate = closureReasonDate;
	}
	public String getClosureDate() {
		return closureDate;
	}
	public void setClosureDate(String closureDate) {
		this.closureDate = closureDate;
	}
	public String getAddressLine1() {
		return addressLine1;
	}
	public void setAddressLine1(String addressLine1) {
		this.addressLine1 = addressLine1;
	}
	public String getClosureReason() {
		return closureReason;
	}
	public void setClosureReason(String closureReason) {
		this.closureReason = closureReason;
	}
	public String getHolderRelationship() {
		return holderRelationship;
	}
	public void setHolderRelationship(String holderRelationship) {
		this.holderRelationship = holderRelationship;
	}
	public String getIssuerTransactionNumber() {
		return issuerTransactionNumber;
	}
	public void setIssuerTransactionNumber(String issuerTransactionNumber) {
		this.issuerTransactionNumber = issuerTransactionNumber;
	}
	public String getBeneficiarySex() {
		return beneficiarySex;
	}
	public void setBeneficiarySex(String beneficiarySex) {
		this.beneficiarySex = beneficiarySex;
	}
	public String getPrimaryCaregiverName() {
		return primaryCaregiverName;
	}
	public void setPrimaryCaregiverName(String primaryCaregiverName) {
		this.primaryCaregiverName = primaryCaregiverName;
	}
	public String getAddressLine3() {
		return addressLine3;
	}
	public void setAddressLine3(String addressLine3) {
		this.addressLine3 = addressLine3;
	}
	public String getAddDate() {
		return addDate;
	}
	public void setAddDate(String addDate) {
		this.addDate = addDate;
	}
	public String getPostalCode() {
		return postalCode;
	}
	public void setPostalCode(String postalCode) {
		this.postalCode = postalCode;
	}
	public String getSpecimenPlan() {
		return specimenPlan;
	}
	public void setSpecimenPlan(String specimenPlan) {
		this.specimenPlan = specimenPlan;
	}
	public String getHolderDateOfBirth() {
		return holderDateOfBirth;
	}
	public void setHolderDateOfBirth(String holderDateOfBirth) {
		this.holderDateOfBirth = holderDateOfBirth;
	}
	public String getOtherSpecimenPlan() {
		return otherSpecimenPlan;
	}
	public void setOtherSpecimenPlan(String otherSpecimenPlan) {
		this.otherSpecimenPlan = otherSpecimenPlan;
	}
	public String getHolderGivenName() {
		return holderGivenName;
	}
	public void setHolderGivenName(String holderGivenName) {
		this.holderGivenName = holderGivenName;
	}
	public String getPrimaryCaregiverType() {
		return primaryCaregiverType;
	}
	public void setPrimaryCaregiverType(String primaryCaregiverType) {
		this.primaryCaregiverType = primaryCaregiverType;
	}
	public String getTransferIndicator() {
		return transferIndicator;
	}
	public void setTransferIndicator(String transferIndicator) {
		this.transferIndicator = transferIndicator;
	}
	public String getTransactionType() {
		return transactionType;
	}
	public void setTransactionType(String transactionType) {
		this.transactionType = transactionType;
	}
	public String getAddressLine2() {
		return addressLine2;
	}
	public void setAddressLine2(String addressLine2) {
		this.addressLine2 = addressLine2;
	}
	public String getRecordType() {
		return recordType;
	}
	public void setRecordType(String recordType) {
		this.recordType = recordType;
	}
	public String getBeneficiarySurname() {
		return beneficiarySurname;
	}
	public void setBeneficiarySurname(String beneficiarySurname) {
		this.beneficiarySurname = beneficiarySurname;
	}
	public String getBeneficiaryGivenName() {
		return beneficiaryGivenName;
	}
	public void setBeneficiaryGivenName(String beneficiaryGivenName) {
		this.beneficiaryGivenName = beneficiaryGivenName;
	}
	public String getBeneficiarySin() {
		return beneficiarySin;
	}
	public void setBeneficiarySin(String beneficiarySin) {
		this.beneficiarySin = beneficiarySin;
	}
	public String getHolderSex() {
		return holderSex;
	}
	public void setHolderSex(String holderSex) {
		this.holderSex = holderSex;
	}
	public String getContract() {
		return contract;
	}
	public void setContract(String contract) {
		this.contract = contract;
	}
	public String getHolderType() {
		return holderType;
	}
	public void setHolderType(String holderType) {
		this.holderType = holderType;
	}
	public String getProvince() {
		return province;
	}
	public void setProvince(String province) {
		this.province = province;
	}
	public String getCountry() {
		return country;
	}
	public void setCountry(String country) {
		this.country = country;
	}
	public String getBeneficiaryDateOfBirth() {
		return beneficiaryDateOfBirth;
	}
	public void setBeneficiaryDateOfBirth(String beneficiaryDateOfBirth) {
		this.beneficiaryDateOfBirth = beneficiaryDateOfBirth;
	}
	public String getOtherContract() {
		return otherContract;
	}
	public void setOtherContract(String otherContract) {
		this.otherContract = otherContract;
	}
	public String getContractSignatureDate() {
		return contractSignatureDate;
	}
	public void setContractSignatureDate(String contractSignatureDate) {
		this.contractSignatureDate = contractSignatureDate;
	}
	public String getRemovalDate() {
		return removalDate;
	}
	public void setRemovalDate(String removalDate) {
		this.removalDate = removalDate;
	}
	public String getContributionDate() {
		return contributionDate;
	}
	public void setContributionDate(String contributionDate) {
		this.contributionDate = contributionDate;
	}
	public String getPrimaryCaregiverSin1OrAgencyBn() {
		return primaryCaregiverSin1OrAgencyBn;
	}
	public void setPrimaryCaregiverSin1OrAgencyBn(String primaryCaregiverSin1OrAgencyBn) {
		this.primaryCaregiverSin1OrAgencyBn = primaryCaregiverSin1OrAgencyBn;
	}
	public String getBondRequestDate() {
		return bondRequestDate;
	}
	public void setBondRequestDate(String bondRequestDate) {
		this.bondRequestDate = bondRequestDate;
	}
	public String getGrantRequested() {
		return grantRequested;
	}
	public void setGrantRequested(String grantRequested) {
		this.grantRequested = grantRequested;
	}
	public String getPrimaryCaregiverSurname1OrAgencyName() {
		return primaryCaregiverSurname1OrAgencyName;
	}
	public void setPrimaryCaregiverSurname1OrAgencyName(String primaryCaregiverSurname1OrAgencyName) {
		this.primaryCaregiverSurname1OrAgencyName = primaryCaregiverSurname1OrAgencyName;
	}
	public String getPrimaryCaregiverType1() {
		return primaryCaregiverType1;
	}
	public void setPrimaryCaregiverType1(String primaryCaregiverType1) {
		this.primaryCaregiverType1 = primaryCaregiverType1;
	}
	public String getPrimaryCaregiverType2() {
		return primaryCaregiverType2;
	}
	public void setPrimaryCaregiverType2(String primaryCaregiverType2) {
		this.primaryCaregiverType2 = primaryCaregiverType2;
	}
	public String getPrimaryCaregiverGivenName2() {
		return primaryCaregiverGivenName2;
	}
	public void setPrimaryCaregiverGivenName2(String primaryCaregiverGivenName2) {
		this.primaryCaregiverGivenName2 = primaryCaregiverGivenName2;
	}
	public String getPrimaryCaregiverSin2OrAgencyBn() {
		return primaryCaregiverSin2OrAgencyBn;
	}
	public void setPrimaryCaregiverSin2OrAgencyBn(String primaryCaregiverSin2OrAgencyBn) {
		this.primaryCaregiverSin2OrAgencyBn = primaryCaregiverSin2OrAgencyBn;
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
	public String getPrimaryCaregiverSurname2OrAgencyName() {
		return primaryCaregiverSurname2OrAgencyName;
	}
	public void setPrimaryCaregiverSurname2OrAgencyName(String primaryCaregiverSurname2OrAgencyName) {
		this.primaryCaregiverSurname2OrAgencyName = primaryCaregiverSurname2OrAgencyName;
	}
	public String getPrimaryCaregiverGivenName1() {
		return primaryCaregiverGivenName1;
	}
	public void setPrimaryCaregiverGivenName1(String primaryCaregiverGivenName1) {
		this.primaryCaregiverGivenName1 = primaryCaregiverGivenName1;
	}
	public String getContributionAmount() {
		return contributionAmount;
	}
	public void setContributionAmount(String contributionAmount) {
		this.contributionAmount = contributionAmount;
	}
	public String getErrorCodes() {
		return errorCodes;
	}
	public void setErrorCodes(String errorCodes) {
		this.errorCodes = errorCodes;
	}
	public String getPrimaryCaregiverGivenName() {
		return primaryCaregiverGivenName;
	}
	public void setPrimaryCaregiverGivenName(String primaryCaregiverGivenName) {
		this.primaryCaregiverGivenName = primaryCaregiverGivenName;
	}
	public String getRetirementSavingRolloverAmount() {
		return retirementSavingRolloverAmount;
	}
	public void setRetirementSavingRolloverAmount(String retirementSavingRolloverAmount) {
		this.retirementSavingRolloverAmount = retirementSavingRolloverAmount;
	}
	public String getRetirementSavingRolloverDate() {
		return retirementSavingRolloverDate;
	}
	public void setRetirementSavingRolloverDate(String retirementSavingRolloverDate) {
		this.retirementSavingRolloverDate = retirementSavingRolloverDate;
	}
	public String getTransactionOrigin() {
		return transactionOrigin;
	}
	public void setTransactionOrigin(String transactionOrigin) {
		this.transactionOrigin = transactionOrigin;
	}
	public String getOriginalIssuerBN() {
		return originalIssuerBN;
	}
	public void setOriginalIssuerBN(String originalIssuerBN) {
		this.originalIssuerBN = originalIssuerBN;
	}
	public String getContractNumber() {
		return contractNumber;
	}
	public void setContractNumber(String contractNumber) {
		this.contractNumber = contractNumber;
	}
	public String getElectionPeriodStartDate() {
		return electionPeriodStartDate;
	}
	public void setElectionPeriodStartDate(String electionPeriodStartDate) {
		this.electionPeriodStartDate = electionPeriodStartDate;
	}
	public String getElectionPeriodEndDate() {
		return electionPeriodEndDate;
	}
	public void setElectionPeriodEndDate(String electionPeriodEndDate) {
		this.electionPeriodEndDate = electionPeriodEndDate;
	}
	public String getEducationSavingRolloverAmount() {
		return educationSavingRolloverAmount;
	}
	public void setEducationSavingRolloverAmount(String educationSavingRolloverAmount) {
		this.educationSavingRolloverAmount = educationSavingRolloverAmount;
	}
	public String getEducationSavingRolloverDate() {
		return educationSavingRolloverDate;
	}
	public void setEducationSavingRolloverDate(String educationSavingRolloverDate) {
		this.educationSavingRolloverDate = educationSavingRolloverDate;
	}
	public String getReportingDate() {
		return reportingDate;
	}
	public void setReportingDate(String reportingDate) {
		this.reportingDate = reportingDate;
	}
	public String getFmvAmount() {
		return fmvAmount;
	}
	public void setFmvAmount(String fmvAmount) {
		this.fmvAmount = fmvAmount;
	}
	public String getTransactionNumber() {
		return transactionNumber;
	}
	public void setTransactionNumber(String transactionNumber) {
		this.transactionNumber = transactionNumber;
	}
	public String getGrantAmount() {
		return grantAmount;
	}
	public void setGrantAmount(String grantAmount) {
		this.grantAmount = grantAmount;
	}
	public String getBondAmount() {
		return bondAmount;
	}
	public void setBondAmount(String bondAmount) {
		this.bondAmount = bondAmount;
	}
	public String getDateOfPayment() {
		return dateOfPayment;
	}
	public void setDateOfPayment(String dateOfPayment) {
		this.dateOfPayment = dateOfPayment;
	}
	public String getRefusalReason() {
		return refusalReason;
	}
	public void setRefusalReason(String refusalReason) {
		this.refusalReason = refusalReason;
	}
	public String getOriginalIssuerBn() {
		return originalIssuerBn;
	}
	public void setOriginalIssuerBn(String originalIssuerBn) {
		this.originalIssuerBn = originalIssuerBn;
	}
	public String getPaymentRequisitioned() {
		return paymentRequisitioned;
	}
	public void setPaymentRequisitioned(String paymentRequisitioned) {
		this.paymentRequisitioned = paymentRequisitioned;
	}
	public String getCdspSystemDate() {
		return cdspSystemDate;
	}
	public void setCdspSystemDate(String cdspSystemDate) {
		this.cdspSystemDate = cdspSystemDate;
	}
	public String getCdspSystemSin() {
		return cdspSystemSin;
	}
	public void setCdspSystemSin(String cdspSystemSin) {
		this.cdspSystemSin = cdspSystemSin;
	}
	public String getBeneficiaryDtcEligibilityYear() {
		return beneficiaryDtcEligibilityYear;
	}
	public void setBeneficiaryDtcEligibilityYear(String beneficiaryDtcEligibilityYear) {
		this.beneficiaryDtcEligibilityYear = beneficiaryDtcEligibilityYear;
	}
	public String getBeneficiaryDtcEligibiltyStatus() {
		return beneficiaryDtcEligibiltyStatus;
	}
	public void setBeneficiaryDtcEligibiltyStatus(String beneficiaryDtcEligibiltyStatus) {
		this.beneficiaryDtcEligibiltyStatus = beneficiaryDtcEligibiltyStatus;
	}
	public String getBeneficiaryDtcUndeterminedReason() {
		return beneficiaryDtcUndeterminedReason;
	}
	public void setBeneficiaryDtcUndeterminedReason(String beneficiaryDtcUndeterminedReason) {
		this.beneficiaryDtcUndeterminedReason = beneficiaryDtcUndeterminedReason;
	}
	public String getDapDate() {
		return dapDate;
	}
	public void setDapDate(String dapDate) {
		this.dapDate = dapDate;
	}
	public String getContributionPortionOfTheNonTaxableFormula() {
		return contributionPortionOfTheNonTaxableFormula;
	}
	public void setContributionPortionOfTheNonTaxableFormula(String contributionPortionOfTheNonTaxableFormula) {
		this.contributionPortionOfTheNonTaxableFormula = contributionPortionOfTheNonTaxableFormula;
	}
	public String getGrantPortionOfTheDap() {
		return grantPortionOfTheDap;
	}
	public void setGrantPortionOfTheDap(String grantPortionOfTheDap) {
		this.grantPortionOfTheDap = grantPortionOfTheDap;
	}
	public String getBondPortionOfTheDap() {
		return bondPortionOfTheDap;
	}
	public void setBondPortionOfTheDap(String bondPortionOfTheDap) {
		this.bondPortionOfTheDap = bondPortionOfTheDap;
	}
	public String getNonTaxablePortionOfTheDap() {
		return nonTaxablePortionOfTheDap;
	}
	public void setNonTaxablePortionOfTheDap(String nonTaxablePortionOfTheDap) {
		this.nonTaxablePortionOfTheDap = nonTaxablePortionOfTheDap;
	}
	public String getTotalDapAmount() {
		return totalDapAmount;
	}
	public void setTotalDapAmount(String totalDapAmount) {
		this.totalDapAmount = totalDapAmount;
	}
	public String getDapRetirementSavingsRolloverAmount() {
		return dapRetirementSavingsRolloverAmount;
	}
	public void setDapRetirementSavingsRolloverAmount(String dapRetirementSavingsRolloverAmount) {
		this.dapRetirementSavingsRolloverAmount = dapRetirementSavingsRolloverAmount;
	}
	public String getLdapDate() {
		return ldapDate;
	}
	public void setLdapDate(String ldapDate) {
		this.ldapDate = ldapDate;
	}
	public String getGrantPortionOfTheLdap() {
		return grantPortionOfTheLdap;
	}
	public void setGrantPortionOfTheLdap(String grantPortionOfTheLdap) {
		this.grantPortionOfTheLdap = grantPortionOfTheLdap;
	}
	public String getBondPortionOfTheLdap() {
		return bondPortionOfTheLdap;
	}
	public void setBondPortionOfTheLdap(String bondPortionOfTheLdap) {
		this.bondPortionOfTheLdap = bondPortionOfTheLdap;
	}
	public String getNonTaxablePortionOfTheLdap() {
		return nonTaxablePortionOfTheLdap;
	}
	public void setNonTaxablePortionOfTheLdap(String nonTaxablePortionOfTheLdap) {
		this.nonTaxablePortionOfTheLdap = nonTaxablePortionOfTheLdap;
	}
	public String getTotalLdapAmount() {
		return totalLdapAmount;
	}
	public void setTotalLdapAmount(String totalLdapAmount) {
		this.totalLdapAmount = totalLdapAmount;
	}
	public String getLdapRetirementSavingsRolloverAmount() {
		return ldapRetirementSavingsRolloverAmount;
	}
	public void setLdapRetirementSavingsRolloverAmount(String ldapRetirementSavingsRolloverAmount) {
		this.ldapRetirementSavingsRolloverAmount = ldapRetirementSavingsRolloverAmount;
	}
	public String getRepaymentDate() {
		return repaymentDate;
	}
	public void setRepaymentDate(String repaymentDate) {
		this.repaymentDate = repaymentDate;
	}
	public String getGrantRepaymentAmount() {
		return grantRepaymentAmount;
	}
	public void setGrantRepaymentAmount(String grantRepaymentAmount) {
		this.grantRepaymentAmount = grantRepaymentAmount;
	}
	public String getBondRepaymentAmount() {
		return bondRepaymentAmount;
	}
	public void setBondRepaymentAmount(String bondRepaymentAmount) {
		this.bondRepaymentAmount = bondRepaymentAmount;
	}
	public String getGrantTerminationAdjustmentAmount() {
		return grantTerminationAdjustmentAmount;
	}
	public void setGrantTerminationAdjustmentAmount(String grantTerminationAdjustmentAmount) {
		this.grantTerminationAdjustmentAmount = grantTerminationAdjustmentAmount;
	}
	public String getBondterminationAdjustmentAmount() {
		return bondterminationAdjustmentAmount;
	}
	public void setBondterminationAdjustmentAmount(String bondterminationAdjustmentAmount) {
		this.bondterminationAdjustmentAmount = bondterminationAdjustmentAmount;
	}
	public String getRepaymentReason() {
		return repaymentReason;
	}
	public void setRepaymentReason(String repaymentReason) {
		this.repaymentReason = repaymentReason;
	}
	public String getFieldName() {
		return fieldName;
	}
	public void setFieldName(String fieldName) {
		this.fieldName = fieldName;
	}
	public String getErrorCode() {
		return errorCode;
	}
	public void setErrorCode(String errorCode) {
		this.errorCode = errorCode;
	}
	public String getSinIssue() {
		return sinIssue;
	}
	public void setSinIssue(String sinIssue) {
		this.sinIssue = sinIssue;
	}
	public String getGivenNameIssue() {
		return givenNameIssue;
	}
	public void setGivenNameIssue(String givenNameIssue) {
		this.givenNameIssue = givenNameIssue;
	}
	public String getSurnameIssue() {
		return surnameIssue;
	}
	public void setSurnameIssue(String surnameIssue) {
		this.surnameIssue = surnameIssue;
	}
	public String getBirthDateIssue() {
		return birthDateIssue;
	}
	public void setBirthDateIssue(String birthDateIssue) {
		this.birthDateIssue = birthDateIssue;
	}
	public String getSexIssue() {
		return sexIssue;
	}
	public void setSexIssue(String sexIssue) {
		this.sexIssue = sexIssue;
	}
	public String getSin() {
		return sin;
	}
	public void setSin(String sin) {
		this.sin = sin;
	}
	public String getOriginalIssuerTransactionNumber() {
		return originalIssuerTransactionNumber;
	}
	public void setOriginalIssuerTransactionNumber(String originalIssuerTransactionNumber) {
		this.originalIssuerTransactionNumber = originalIssuerTransactionNumber;
	}
	public String getStopRequestDate() {
		return stopRequestDate;
	}
	public void setStopRequestDate(String stopRequestDate) {
		this.stopRequestDate = stopRequestDate;
	}
	public String getCurrentContractStatus() {
		return currentContractStatus;
	}
	public void setCurrentContractStatus(String currentContractStatus) {
		this.currentContractStatus = currentContractStatus;
	}
	public String getContractInformationPassesTransactionValidation() {
		return contractInformationPassesTransactionValidation;
	}
	public void setContractInformationPassesTransactionValidation(String contractInformationPassesTransactionValidation) {
		this.contractInformationPassesTransactionValidation = contractInformationPassesTransactionValidation;
	}
	public String getContractInformationPasses60DayRule() {
		return contractInformationPasses60DayRule;
	}
	public void setContractInformationPasses60DayRule(String contractInformationPasses60DayRule) {
		this.contractInformationPasses60DayRule = contractInformationPasses60DayRule;
	}
	public String getContractInformationContainsMinimumInformationRequirements() {
		return contractInformationContainsMinimumInformationRequirements;
	}
	public void setContractInformationContainsMinimumInformationRequirements(
			String contractInformationContainsMinimumInformationRequirements) {
		this.contractInformationContainsMinimumInformationRequirements = contractInformationContainsMinimumInformationRequirements;
	}
	public String getBeneficiarySinPassesIdentityValidationAtSir() {
		return beneficiarySinPassesIdentityValidationAtSir;
	}
	public void setBeneficiarySinPassesIdentityValidationAtSir(String beneficiarySinPassesIdentityValidationAtSir) {
		this.beneficiarySinPassesIdentityValidationAtSir = beneficiarySinPassesIdentityValidationAtSir;
	}
	public String getHoldersSinPassesIdentityValidationAtSir() {
		return holdersSinPassesIdentityValidationAtSir;
	}
	public void setHoldersSinPassesIdentityValidationAtSir(String holdersSinPassesIdentityValidationAtSir) {
		this.holdersSinPassesIdentityValidationAtSir = holdersSinPassesIdentityValidationAtSir;
	}
	public String getCurrentContractIsWaitingForATransferToOccur() {
		return currentContractIsWaitingForATransferToOccur;
	}
	public void setCurrentContractIsWaitingForATransferToOccur(String currentContractIsWaitingForATransferToOccur) {
		this.currentContractIsWaitingForATransferToOccur = currentContractIsWaitingForATransferToOccur;
	}
	public String getBeneficiaryPassesResidencyValidationAtContractSignatureDate() {
		return beneficiaryPassesResidencyValidationAtContractSignatureDate;
	}
	public void setBeneficiaryPassesResidencyValidationAtContractSignatureDate(
			String beneficiaryPassesResidencyValidationAtContractSignatureDate) {
		this.beneficiaryPassesResidencyValidationAtContractSignatureDate = beneficiaryPassesResidencyValidationAtContractSignatureDate;
	}
	public String getBeneficiaryPassesDtcEligibilityValidationAtContractSignatureDate() {
		return beneficiaryPassesDtcEligibilityValidationAtContractSignatureDate;
	}
	public void setBeneficiaryPassesDtcEligibilityValidationAtContractSignatureDate(
			String beneficiaryPassesDtcEligibilityValidationAtContractSignatureDate) {
		this.beneficiaryPassesDtcEligibilityValidationAtContractSignatureDate = beneficiaryPassesDtcEligibilityValidationAtContractSignatureDate;
	}
	public String getBeneficiarySinIsUsableAtContractSignatureDate() {
		return beneficiarySinIsUsableAtContractSignatureDate;
	}
	public void setBeneficiarySinIsUsableAtContractSignatureDate(String beneficiarySinIsUsableAtContractSignatureDate) {
		this.beneficiarySinIsUsableAtContractSignatureDate = beneficiarySinIsUsableAtContractSignatureDate;
	}
	
	public String getHoldersSinIsUsableAtContractSignatureDate() {
		return holdersSinIsUsableAtContractSignatureDate;
	}
	public void setHoldersSinIsUsableAtContractSignatureDate(String holdersSinIsUsableAtContractSignatureDate) {
		this.holdersSinIsUsableAtContractSignatureDate = holdersSinIsUsableAtContractSignatureDate;
	}
	public String getRemainingBalanceOnContract() {
		return remainingBalanceOnContract;
	}
	public void setRemainingBalanceOnContract(String remainingBalanceOnContract) {
		this.remainingBalanceOnContract = remainingBalanceOnContract;
	}
	public String getCurrentReasonForChangeOfContractStatus() {
		return currentReasonForChangeOfContractStatus;
	}
	public void setCurrentReasonForChangeOfContractStatus(String currentReasonForChangeOfContractStatus) {
		this.currentReasonForChangeOfContractStatus = currentReasonForChangeOfContractStatus;
	}
	public String getCurrentTransferStatus() {
		return currentTransferStatus;
	}
	public void setCurrentTransferStatus(String currentTransferStatus) {
		this.currentTransferStatus = currentTransferStatus;
	}
	public String getCurrentResidencyEligibilityOfBeneficiary() {
		return currentResidencyEligibilityOfBeneficiary;
	}
	public void setCurrentResidencyEligibilityOfBeneficiary(String currentResidencyEligibilityOfBeneficiary) {
		this.currentResidencyEligibilityOfBeneficiary = currentResidencyEligibilityOfBeneficiary;
	}
	public String getCurrentDtcEligibilityOfBeneficiary() {
		return currentDtcEligibilityOfBeneficiary;
	}
	public void setCurrentDtcEligibilityOfBeneficiary(String currentDtcEligibilityOfBeneficiary) {
		this.currentDtcEligibilityOfBeneficiary = currentDtcEligibilityOfBeneficiary;
	}
	public String getCurrentBeneficiarySinUsability() {
		return currentBeneficiarySinUsability;
	}
	public void setCurrentBeneficiarySinUsability(String currentBeneficiarySinUsability) {
		this.currentBeneficiarySinUsability = currentBeneficiarySinUsability;
	}
	public String getCurrentHoldersSinUsability() {
		return currentHoldersSinUsability;
	}
	public void setCurrentHoldersSinUsability(String currentHoldersSinUsability) {
		this.currentHoldersSinUsability = currentHoldersSinUsability;
	}
	public String getContractRegistrationRetirementSavingsRolloverCompliant() {
		return contractRegistrationRetirementSavingsRolloverCompliant;
	}
	public void setContractRegistrationRetirementSavingsRolloverCompliant(
			String contractRegistrationRetirementSavingsRolloverCompliant) {
		this.contractRegistrationRetirementSavingsRolloverCompliant = contractRegistrationRetirementSavingsRolloverCompliant;
	}
	public String getContractRegistrationEducationSavingsRolloverCompliant() {
		return contractRegistrationEducationSavingsRolloverCompliant;
	}
	public void setContractRegistrationEducationSavingsRolloverCompliant(
			String contractRegistrationEducationSavingsRolloverCompliant) {
		this.contractRegistrationEducationSavingsRolloverCompliant = contractRegistrationEducationSavingsRolloverCompliant;
	}
	
	
	
}
