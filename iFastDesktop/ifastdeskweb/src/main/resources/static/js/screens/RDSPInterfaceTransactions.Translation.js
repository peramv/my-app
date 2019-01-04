/*********************************************************************************************
 * @file	RDSPTransactionsInterface.Translation.js
 * @author	Danil Gorelic
 * @desc	Resources JS file for RDSPTransactionsInterface.
 *********************************************************************************************/

DesktopWeb.ScreenTranslation = {
	'enUS': {
		RunNo: 'Run No',
		OK: 'OK',
		TransactionDescriptions : [
			{
				key: {
					recordType: "101",
					transType: "01"
				},
				text: "Contract Information"
			},
			{
				key: {
					recordType: "101",
					transType: "02"
				},
				text: "Beneficiary Information"
			},
			{
				key: {
					recordType: "101",
					transType: "03"
				},
				text: "Holder Information"
			},
			{
				key: {
					recordType: "102",
					transType: "10"
				},
				text: "Close a Contract"
			},
			{
				key: {
					recordType: "102",
					transType: "11"
				},
				text: "Rename a Contract"
			},
			{
				key: {
					recordType: "201",
					transType: "02"
				},
				text: "Update Beneficiary Information"
			},
			{
				key: {
					recordType: "201",
					transType: "03"
				},
				text: "Update Holder Information"
			},
			{
				key: {
					recordType: "201",
					transType: "13"
				},
				text: "Add Holder to Contract"
			},
			{
				key: {
					recordType: "201",
					transType: "23"
				},
				text: "Remove Holder from Contract"
			},
			{
				key: {
					recordType: "202",
					transType: "01"
				},
				text: "Add or Update Consent for Beneficiary"
			},
			{
				key: {
					recordType: "202",
					transType: "02"
				},
				text: "Revoke Consent for Beneficiary"
			},
			{
				key: {
					recordType: "401",
					transType: "01"
				},
				text: "Contribution / Grant Request"
			},
			{
				key: {
					recordType: "401",
					transType: "02"
				},
				text: "Correction of Contribution / Grant Request"
			},
			{
				key: {
					recordType: "401",
					transType: "05"
				},
				text: "Bond Payment Request"
			},
			{
				key: {
					recordType: "401",
					transType: "06"
				},
				text: "Stop Bond Payment Request"
			},
			{
				key: {
					recordType: "401",
					transType: "08"
				},
				text: "Retirement Savings Rollover"
			},
			{
				key: {
					recordType: "401",
					transType: "09"
				},
				text: "Retirement Savings Rollover Reversal"
			},
			{
				key: {
					recordType: "401",
					transType: "10"
				},
				text: "Repayment of Grant and/or Bond"
			},
			{
				key: {
					recordType: "401",
					transType: "11"
				},
				text: "Reverse Repayment of Grant and/or Bond"
			},
			{
				key: {
					recordType: "401",
					transType: "20"
				},
				text: "DAP"
			},
			{
				key: {
					recordType: "401",
					transType: "21"
				},
				text: "LDAP"
			},
			{
				key: {
					recordType: "401",
					transType: "22"
				},
				text: "DAP Reversal"
			},
			{
				key: {
					recordType: "401",
					transType: "23"
				},
				text: "LDAP Reversal"
			},
			{
				key: {
					recordType: "401",
					transType: "30"
				},
				text: "Education Savings Rollover"
			},
			{
				key: {
					recordType: "401",
					transType: "31"
				},
				text: "Education Savings Rollover Reversal"
			},
			{
				key: {
					recordType: "501",
					transType: "01"
				},
				text: "Episodic DTC Election"
			},
			{
				key: {
					recordType: "501",
					transType: "02"
				},
				text: "Episodic DTC Election Reversal"
			},
			{
				key: {
					recordType: "501",
					transType: "03"
				},
				text: "SDSP Election"
			},
			{
				key: {
					recordType: "801",
					transType: ""
				},
				text: "Error Record"
			},
			{
				key: {
					recordType: "851",
					transType: ""
				},
				text: "Severe Error"
			},
			{
				key: {
					recordType: "921",
					transType: ""
				},
				text: "SIN Usability"
			},
			{
				key: {
					recordType: "951",
					transType: ""
				},
				text: "Contract Status"
			},
			{
				key: {
					recordType: "952",
					transType: ""
				},
				text: "Episodic DTC Election"
			},
			{
				key: {
					recordType: "953",
					transType: ""
				},
				text: "SDSP Election"
			},
			{
				key: {
					recordType: "981",
					transType: ""
				},
				text: "Beneficiary DTC Eligibility"
			},
			{
				key: {
					recordType: "901",
					transType: ""
				},
				text: "Transaction Processing"
			},
			{
				key: {
					recordType: "971",
					transType: ""
				},
				text: "Transfer Extract Information"
			}

		],
		
		FileType : "File Type",
		fileTypeMap : {
			All: "All",
			Incoming: "Incoming",
			Outgoing: "Outgoing"		
		},
		
		RecordType : "Record Type",
		recordTypeMap : {
			All: "All",
			101: "RT101",
			102: "RT102",
			201: "RT201",
			202: "RT202",
			401: "RT401",
			501: "RT501",
			701: "RT701"
		},
		
		Status : "Status",
		statusMap : {
			All: "All",
			New: "New",
			Hold: "Hold",
			ReadyToSend: "Ready To Send",
			Failed: "Failed",
			Refused: "Refused",
			Rejected: "Rejected",
			Sent: "Sent",
			Accepted: "Accepted"
		},	
		
		NewStatus:  "Change status of selected record",
		newStatusMap : {
			Hold : 'Hold', 
			ReadyToSend: 'Ready To Send'
		},
		
		AccountNo : "Account No",
		Year : "Year",
		Refresh: "Refresh",
		More: "More",
		ContractRegStatus : "Contract Registration Status",
		DTCElectionCurr : "DTC Election (current)",
		SDSPElectionCurr : "SDSP Election (current)",
		RDSPBeneInfo: "RDSP Beneficiary Information",
		BeneName:"Beneficiary Name",
		BeneDOB: "Date of Birth",
		ContEndDate: "Contribution End Date",
		GrantEligibleEndDate : "Grant Eligibility End Date",
		SpecimenPlanNum : "Specimen Plan Number",
		DateOfDeath : "Date of Death",
		SIN : "SIN",
		BondEligibleEndDate: "Bond Eligibility End Date",
		AccHolderName : "Name",
		SINorBN : "SIN/BN",
		RelationToBene : "Relationship to Beneficiary", 
		RDSPAccountHolderOrPCGInformation:"RDSP Account Holder/PCG Information",
		RdspTransRecords:"RDSP Transaction Records",
		Account: 	"Account",
		TransDate:	"Trans Date",
		ESDCTransNo:"ESDC Trans No.",
		TransType:	"Trans Type",
		TransDescr: "Trans Description",
		RecordDetails : 'Record Details',
		GenerateFile : 'Generate File',
		detailsMap : {
				recordType: 'Record Type',
				transType: 'Transaction Type',
				issuerBN: 'Issuer BN',
				issuerTransNo: 'Issuer Transaction Number',
				specimenPlan: 'Specimen Plan',
				contract: 'Contract',
				signDate: 'Contract Signature Date',
				pcgId: 'Primary Caregiverv SIN/BN',
				pcgName: 'Primary Caregiver Name',
				pcgSN: 'Primary Caregiver Surname or Agency Name',
				pcgType: 'Primary Caregiver Type',
				transferIndicator: 'Transfer Indicator',
				updateDate: 'Contract Creation or Update Date',
				otherContract: 'Other Contract',
				otherSpecimenPlan: 'Specimen Plan'
		},
		ErrorMessages     : "Error Messages",
		HolderSinOrBn		:"Holder SIN Or BN",
		PrimaryCaregiverSinOrAgencyBn		:"Primary Caregiver SIN Or Agency BN",
		City		:"City",
		IssuerBn		:"Issuer BN",
		ContractCreationOrUpdateDate		:"Contract Creation Or Update Date",
		PrimaryCaregiverSurnameOrAgencyName		:"Primary Caregiver Surname Or Agency Name",
		UpdateDate		:"Update Date",
		HolderSurnameOrHolderAgencyName		:"Holder Surname Or Holder Agency Name",
		Language		:"Language",
		ClosureReasonDate		:"Closure Reason Date",
		ClosureDate		:"Closure Date",
		AddressLine1		:"Address Line 1",
		ClosureReason		:"Closure Reason",
		HolderRelationship		:"Holder Relationship",
		IssuerTransactionNumber		:"Issuer Transaction Number",
		BeneficiarySex		:"Beneficiary Sex",
		PrimaryCaregiverName		:"Primary Caregiver Name",
		AddressLine3		:"Address Line 3",
		AddDate		:"Add Date",
		PostalCode		:"Postal Code",
		SpecimenPlan		:"Specimen Plan",
		HolderDateOfBirth		:"Holder Date Of Birth",
		OtherSpecimenPlan		:"Other Specimen Plan",
		HolderGivenName		:"Holder Given Name",
		PrimaryCaregiverType		:"Primary Caregiver Type",
		TransferIndicator		:"Transfer Indicator",
		TransactionType		:"Transaction Type",
		AddressLine2		:"Address Line 2",
		RecordType		:"Record Type",
		BeneficiarySurname		:"Beneficiary Surname",
		BeneficiaryGivenName		:"Beneficiary Given Name",
		BeneficiarySin		:"Beneficiary SIN",
		HolderSex		:"Holder Sex",
		Contract		:"Contract",
		HolderType		:"Holder Type",
		Province		:"Province",
		Country		:"Country",
		BeneficiaryDateOfBirth		:"Beneficiary Date Of Birth",
		OtherContract		:"Other Contract",
		ContractSignatureDate		:"Contract Signature Date",
		RemovalDate     :  "Removal Date",
		ContributionDate      :"Contribution Date",
		PrimaryCaregiverSin1OrAgencyBn      :"Primary Caregiver SIN 1 Or Agency BN",
		BondRequestDate      :"Bond Request Date", 
		GrantRequested      :"Grant Requested",
		PrimaryCaregiverSurname1OrAgencyName      :"Primary Caregiver Surname 1 Or Agency Name",
		PrimaryCaregiverType1      :"Primary Caregiver Type 1",
		PrimaryCaregiverType2      :"Primary Caregiver Type 2",
		PrimaryCaregiverGivenName2      :"Primary Caregiver Given Name 2",
		PrimaryCaregiverSin2OrAgencyBn      :"Primary Caregiver SIN 2 Or Agency BN",
		CertificationDate      :"Certification Date",
		TransactionDate      :"Transaction Date",
		PrimaryCaregiverSurname2OrAgencyName      :"Primary Caregiver Surname 2 Or Agency Name",
		PrimaryCaregiverGivenName1      :"Primary Caregiver Given Name 1",
		ContributionAmount      :"Contribution Amount",
		PrimaryCaregiverGivenName     :"Primary Caregiver Given Name", 
		RetirementSavingRolloverAmount     :"Retirement Saving Rollover Amount",
		RetirementSavingRolloverDate     :"Retirement Saving Rollover Date",
		TransactionOrigin:"Transaction Origin", 
		OriginalIssuerBN:"Originl Issuer BN", 
		ContractNumber:"Contract Number", 
		ElectionPeriodStartDate:"Election Period Start Date", 
		ElectionPeriodEndDate:"Election Period End Date",
		EducationSavingRolloverAmount	:"Education Saving Rollover Amount",
		EducationSavingRolloverDate	:"Education Saving Rollover Date",
		ReportingDate	:"Reporting Date",
		FmvAmount	:"FMV Amount",
		TransactionNumber	:"Transaction Number",
		GrantAmount	:"Grant Amount",
		BondAmount	:"Bond Amount",
		DateOfPayment	:"Date Of Payment",
		RefusalReason	:"Refusal Reason",
		OriginalIssuerBn	:"Original Issuer BN",
		OriginalTransactionNumber	:"Original Transaction Number",
		PaymentRequisitioned	:"Payment Requisitioned",
		CdspSystemDate	:"CDSP System Date",
		CdspSystemSin	:"CDSP System SIN",
		AddConsentDate: "Add Consent Date",
		ConsentSinOrBn: "Consent SIN Or BN",
		ConsentGivenName: "Consent Given Name",
		ConsentSurnameOrAgencyName: "Consent Surname Or Agency Name",
		ConsentType: "Consent Type",
		RevokeConsentDate: "Revoke Consent Date",
		BeneficiaryDtcEligibilityYear: "Beneficiary DTC Eligibility Year",
		BeneficiaryDtcEligibiltyStatus: "Beneficiary DTC Eligibility Status",
		BeneficiaryDtcUndeterminedReason: "Beneficiary DTC Undetermined Reason",
		DapDate:"DAP Date",
		ContributionPortionOfTheNonTaxableFormula:"Contribution Portion of the Non-Taxable Formula",
		GrantPortionOfTheDap:"Grant Portion of the DAP",
		BondPortionOfTheDap:"Bond Portion of the DAP",
		NonTaxablePortionOfTheDap:"Non Taxable Portion of the DAP",
		TotalDapAmount:"Total DAP Amount",
		DapRetirementSavingsRolloverAmount:"DAP Retirement Savings Rollover Amount",
		LdapDate:"LDAP Date",
		GrantPortionOfTheLdap:"Grant Portion of the LDAP",
		BondPortionOfTheLdap:"Bond Portion of the LDAP",
		NonTaxablePortionOfTheLdap:"Non Taxable Portion of the LDAP",
		TotalLdapAmount:"Total LDAP Amount",
		LdapRetirementSavingsRolloverAmount:"LDAP Retirement Savings Rollover Amount",
		RepaymentDate:"Repayment Date",
		GrantRepaymentAmount:"Grant Repayment Amount",
		BondRepaymentAmount:"Bond Repayment Amount",
		GrantTerminationAdjustmentAmount:"Grant Termination Adjustment Amount",
		BondterminationAdjustmentAmount:"Bond Termination Adjustment Amount",
		RepaymentReason:"Repayment Reason",
		FieldName:"Field Name",
		ErrorCode:"Error Code",
		SinIssue:"Sin Issue",
		GivenNameIssue:"Given Name Issue",
		SurnameIssue:"Surname Issue",
		BirthDateIssue:"Birth Date Issue",
		SexIssue:"Sex Issue",
		Sin:"SIN",
		OriginalIssuerTransactionNumber: "Original Issuer Transaction Number",
		StopRequestDate:"Stop Request Date",
		CurrentContractStatus:"Current Contract Status ",
  		ContractInformationPassesTransactionValidation:"Contract Information Transaction Validation",
  		ContractInformationPasses60DayRule:"Passed 60 day rule",
  		ContractInformationContainsMinimumInformationRequirements:"Passed Min Information Requirements",
  		BeneficiarySinPassesIdentityValidationAtSir:"Passed Bene SIN Identity Validation",
  		HoldersSinPassesIdentityValidationAtSir:"Passed Holder SIN Identity Validation ",
  		CurrentContractIsWaitingForATransferToOccur:"Current Contract awaiting transfer",
  		BeneficiaryPassesResidencyValidationAtContractSignatureDate:"Bene Residency passed at Contract Signature Date",
  		BeneficiaryPassesDtcEligibilityValidationAtContractSignatureDate:"Bene DTC eligible at Contract Signature Date",
  		BeneficiarySinIsUsableAtContractSignatureDate:"Bene SIN usable at Contract Signature Date",
  		HoldersSinIsUsableAtContractSignatureDate:"Holder SIN usable at Contract Signature Date",
  		RemainingBalanceOnContract:"Remaining Balance on Contract ",
  		CurrentReasonForChangeOfContractStatus:"Current Reason for Contract Status Change",
  		CurrentTransferStatus:"Current Transfer Status",
  		CurrentResidencyEligibilityOfBeneficiary:"Current Residency eligibility of bene",
  		CurrentDtcEligibilityOfBeneficiary:"Current DTC eligibility of bene",
  		CurrentBeneficiarySinUsability:"Current Bene SIN usability",
  		CurrentHoldersSinUsability:"Current Holder SIN Usability",
  		ContractRegistrationRetirementSavingsRolloverCompliant:"RSP R/O Compliant",
		ContractRegistrationEducationSavingsRolloverCompliant:"RESP R/O Compliant"

		
			
	}	
	
	,'frCA': {
		'enUS': {
			RunNo: 'Run No',
			OK: 'OK',
			TransactionDescriptions : [
				{
					key: {
						recordType: "101",
						transType: "01"
					},
					text: "Contract Information"
				},
				{
					key: {
						recordType: "101",
						transType: "02"
					},
					text: "Beneficiary Information"
				},
				{
					key: {
						recordType: "101",
						transType: "03"
					},
					text: "Holder Information"
				},
				{
					key: {
						recordType: "102",
						transType: "10"
					},
					text: "Close a Contract"
				},
				{
					key: {
						recordType: "102",
						transType: "11"
					},
					text: "Rename a Contract"
				},
				{
					key: {
						recordType: "201",
						transType: "02"
					},
					text: "Update Beneficiary Information"
				},
				{
					key: {
						recordType: "201",
						transType: "03"
					},
					text: "Update Holder Information"
				},
				{
					key: {
						recordType: "201",
						transType: "13"
					},
					text: "Add Holder to Contract"
				},
				{
					key: {
						recordType: "201",
						transType: "23"
					},
					text: "Remove Holder from Contract"
				},
				{
					key: {
						recordType: "202",
						transType: "01"
					},
					text: "Add or Update Consent for Beneficiary"
				},
				{
					key: {
						recordType: "202",
						transType: "02"
					},
					text: "Revoke Consent for Beneficiary"
				},
				{
					key: {
						recordType: "401",
						transType: "01"
					},
					text: "Contribution / Grant Request"
				},
				{
					key: {
						recordType: "401",
						transType: "02"
					},
					text: "Correction of Contribution / Grant Request"
				},
				{
					key: {
						recordType: "401",
						transType: "05"
					},
					text: "Bond Payment Request"
				},
				{
					key: {
						recordType: "401",
						transType: "06"
					},
					text: "Stop Bond Payment Request"
				},
				{
					key: {
						recordType: "401",
						transType: "08"
					},
					text: "Retirement Savings Rollover"
				},
				{
					key: {
						recordType: "401",
						transType: "09"
					},
					text: "Retirement Savings Rollover Reversal"
				},
				{
					key: {
						recordType: "401",
						transType: "10"
					},
					text: "Repayment of Grant and/or Bond"
				},
				{
					key: {
						recordType: "401",
						transType: "11"
					},
					text: "Reverse Repayment of Grant and/or Bond"
				},
				{
					key: {
						recordType: "401",
						transType: "20"
					},
					text: "DAP"
				},
				{
					key: {
						recordType: "401",
						transType: "21"
					},
					text: "LDAP"
				},
				{
					key: {
						recordType: "401",
						transType: "22"
					},
					text: "DAP Reversal"
				},
				{
					key: {
						recordType: "401",
						transType: "23"
					},
					text: "LDAP Reversal"
				},
				{
					key: {
						recordType: "401",
						transType: "30"
					},
					text: "Education Savings Rollover"
				},
				{
					key: {
						recordType: "401",
						transType: "31"
					},
					text: "Education Savings Rollover Reversal"
				},
				{
					key: {
						recordType: "501",
						transType: "01"
					},
					text: "Episodic DTC Election"
				},
				{
					key: {
						recordType: "501",
						transType: "02"
					},
					text: "Episodic DTC Election Reversal"
				},
				{
					key: {
						recordType: "501",
						transType: "03"
					},
					text: "SDSP Election"
				}
			],
			
			FileType : "File Type",
			fileTypeMap : {
				All: "All",
				Incoming: "Incoming",
				Outgoing: "Outgoing"		
			},
			
			RecordType : "Record Type",
			recordTypeMap : {
				All: "All",
				101: "RT101",
				102: "RT102",
				201: "RT201",
				202: "RT202",
				401: "RT401",
				501: "RT501",
				701: "RT701"
			},
			
			Status : "Status",
			statusMap : {
				All: "All",
				New: "New",
				Hold: "Hold",
				ReadyToSend: "Ready To Send",
				Failed: "Failed",
				Refused: "Refused",
				Rejected: "Rejected",
				Sent: "Sent",
				Accepted: "Accepted"
			},	
			
			NewStatus:  "Change status of selected record",
			newStatusMap : {
				Hold : 'Hold', 
				ReadyToSend: 'Ready To Send'
			},
			
			AccountNo : "Account No",
			Year : "Year",
			Refresh: "Refresh",
			More: "More",
			ContractRegStatus : "Contract Registration Status",
			DTCElectionCurr : "DTC Election (current)",
			SDSPElectionCurr : "SDSP Election (current)",
			RDSPBeneInfo: "RDSP Beneficiary Information",
			BeneName:"Beneficiary Name",
			BeneDOB: "Date of Birth",
			ContEndDate: "Contribution End Date",
			GrantEligibleEndDate : "Grant Eligibility End Date",
			SpecimenPlanNum : "Specimen Plan Number",
			DateOfDeath : "Date of Death",
			SIN : "SIN",
			BondEligibleEndDate: "Bond Eligibility End Date",
			AccHolderName : "Name",
			SINorBN : "SIN/BN",
			RelationToBene : "Relationship to Beneficiary", 
			RDSPAccountHolderOrPCGInformation:"RDSP Account Holder/PCG Information",
			RdspTransRecords:"RDSP Transaction Records",
			Account: 	"Account",
			TransDate:	"Trans Date",
			ESDCTransNo:"ESDC Trans No.",
			TransType:	"Trans Type",
			TransDescr: "Trans Description",
			RecordDetails : 'Record Details',
			GenerateFile : 'Generate File',
			detailsMap : {
					recordType: 'Record Type',
					transType: 'Transaction Type',
					issuerBN: 'Issuer BN',
					issuerTransNo: 'Issuer Transaction Number',
					specimenPlan: 'Specimen Plan',
					contract: 'Contract',
					signDate: 'Contract Signature Date',
					pcgId: 'Primary Caregiverv SIN/BN',
					pcgName: 'Primary Caregiver Name',
					pcgSN: 'Primary Caregiver Surname or Agency Name',
					pcgType: 'Primary Caregiver Type',
					transferIndicator: 'Transfer Indicator',
					updateDate: 'Contract Creation or Update Date',
					otherContract: 'Other Contract',
					otherSpecimenPlan: 'Specimen Plan'
			},
			ErrorMessages     : "Error Messages",
			HolderSinOrBn		:"Holder SIN Or BN",
			PrimaryCaregiverSinOrAgencyBn		:"Primary Caregiver SIN Or Agency BN",
			City		:"City",
			IssuerBn		:"Issuer BN",
			ContractCreationOrUpdateDate		:"Contract Creation Or Update Date",
			PrimaryCaregiverSurnameOrAgencyName		:"Primary Caregiver Surname Or Agency Name",
			UpdateDate		:"Update Date",
			HolderSurnameOrHolderAgencyName		:"Holder Surname Or Holder Agency Name",
			Language		:"Language",
			ClosureReasonDate		:"Closure Reason Date",
			ClosureDate		:"Closure Date",
			AddressLine1		:"Address Line 1",
			ClosureReason		:"Closure Reason",
			HolderRelationship		:"Holder Relationship",
			IssuerTransactionNumber		:"Issuer Transaction Number",
			BeneficiarySex		:"Beneficiary Sex",
			PrimaryCaregiverName		:"Primary Caregiver Name",
			AddressLine3		:"Address Line 3",
			AddDate		:"Add Date",
			PostalCode		:"Postal Code",
			SpecimenPlan		:"Specimen Plan",
			HolderDateOfBirth		:"Holder Date Of Birth",
			OtherSpecimenPlan		:"Other Specimen Plan",
			HolderGivenName		:"Holder Given Name",
			PrimaryCaregiverType		:"Primary Caregiver Type",
			TransferIndicator		:"Transfer Indicator",
			TransactionType		:"Transaction Type",
			AddressLine2		:"Address Line 2",
			RecordType		:"Record Type",
			BeneficiarySurname		:"Beneficiary Surname",
			BeneficiaryGivenName		:"Beneficiary Given Name",
			BeneficiarySin		:"Beneficiary SIN",
			HolderSex		:"Holder Sex",
			Contract		:"Contract",
			HolderType		:"Holder Type",
			Province		:"Province",
			Country		:"Country",
			BeneficiaryDateOfBirth		:"Beneficiary Date Of Birth",
			OtherContract		:"Other Contract",
			ContractSignatureDate		:"Contract Signature Date",
			RemovalDate     :  "Removal Date",
			ContributionDate      :"Contribution Date",
			PrimaryCaregiverSin1OrAgencyBn      :"Primary Caregiver SIN 1 Or Agency BN",
			BondRequestDate      :"Bond Request Date", 
			GrantRequested      :"Grant Requested",
			PrimaryCaregiverSurname1OrAgencyName      :"Primary Caregiver Surname 1 Or Agency Name",
			PrimaryCaregiverType1      :"Primary Caregiver Type 1",
			PrimaryCaregiverType2      :"Primary Caregiver Type 2",
			PrimaryCaregiverGivenName2      :"Primary Caregiver Given Name 2",
			PrimaryCaregiverSin2OrAgencyBn      :"Primary Caregiver SIN 2 Or Agency BN",
			CertificationDate      :"Certification Date",
			TransactionDate      :"Transaction Date",
			PrimaryCaregiverSurname2OrAgencyName      :"Primary Caregiver Surname 2 Or Agency Name",
			PrimaryCaregiverGivenName1      :"Primary Caregiver Given Name 1",
			ContributionAmount      :"Contribution Amount",
			PrimaryCaregiverGivenName     :"Primary Caregiver Given Name", 
			RetirementSavingRolloverAmount     :"Retirement Saving Rollover Amount",
			RetirementSavingRolloverDate     :"Retirement Saving Rollover Date",
			EducationSavingRolloverAmount	:"Education Saving Rollover Amount",
			EducationSavingRolloverDate	:"Education Saving Rollover Date",
			ReportingDate	:"Reporting Date",
			FmvAmount	:"FMV Amount",
			TransactionNumber	:"Transaction Number",
			GrantAmount	:"Grant Amount",
			BondAmount	:"Bond Amount",
			DateOfPayment	:"Date Of Payment",
			RefusalReason	:"Refusal Reason",
			OriginalIssuerBn	:"Original Issuer BN",
			OriginalTransactionNumber	:"Original Transaction Number",
			PaymentRequisitioned	:"Payment Requisitioned",
			CdspSystemDate	:"CDSP System Date",
			CdspSystemSin	:"CDSP System SIN",
			AddConsentDate: "Add Consent Date",
			ConsentSinOrBn: "Consent SIN Or BN",
			ConsentGivenName: "Consent Given Name",
			ConsentSurnameOrAgencyName: "Consent Surname Or Agency Name",
			ConsentType: "Consent Type",
			RevokeConsentDate: "Revoke Consent Date",
			BeneficiaryDtcEligibilityYear: "Beneficiary DTC Eligibility Year",
			BeneficiaryDtcEligibiltyStatus: "Beneficiary DTC Eligibility Status",
			BeneficiaryDtcUndeterminedReason: "Beneficiary DTC Undetermined Reason",
			DapDate:"DAP Date",
			ContributionPortionOfTheNonTaxableFormula:"Contribution Portion of the Non-Taxable Formula",
			GrantPortionOfTheDap:"Grant Portion of the DAP",
			BondPortionOfTheDap:"Bond Portion of the DAP",
			NonTaxablePortionOfTheDap:"Non Taxable Portion of the DAP",
			TotalDapAmount:"Total DAP Amount",
			DapRetirementSavingsRolloverAmount:"DAP Retirement Savings Rollover Amount",
			LdapDate:"LDAP Date",
			GrantPortionOfTheLdap:"Grant Portion of the LDAP",
			BondPortionOfTheLdap:"Bond Portion of the LDAP",
			NonTaxablePortionOfTheLdap:"Non Taxable Portion of the LDAP",
			TotalLdapAmount:"Total LDAP Amount",
			LdapRetirementSavingsRolloverAmount:"LDAP Retirement Savings Rollover Amount",
			RepaymentDate:"Repayment Date",
			GrantRepaymentAmount:"Grant Repayment Amount",
			BondRepaymentAmount:"Bond Repayment Amount",
			GrantTerminationAdjustmentAmount:"Grant Termination Adjustment Amount",
			BondterminationAdjustmentAmount:"Bond Termination Adjustment Amount",
			RepaymentReason:"Repayment Reason",
			FieldName:"Field Name",
			ErrorCode:"Error Code",
			SinIssue:"Sin Issue",
			GivenNameIssue:"Given Name Issue",
			SurnameIssue:"Surname Issue",
			BirthDateIssue:"Birth Date Issue",
			SexIssue:"Sex Issue",
			Sin:"SIN",
			OriginalIssuerTransactionNumber: "Original Issuer Transaction Number",
			StopRequestDate:"Stop Request Date",
			CurrentContractStatus:"Current Contract Status ",
	  		ContractInformationPassesTransactionValidation:"Contract Information Transaction Validation",
	  		ContractInformationPasses60DayRule:"Passed 60 day rule",
	  		ContractInformationContainsMinimumInformationRequirements:"Passed Min Information Requirements",
	  		BeneficiarySinPassesIdentityValidationAtSir:"Passed Bene SIN Identity Validation",
	  		HoldersSinPassesIdentityValidationAtSir:"Passed Holder SIN Identity Validation ",
	  		CurrentContractIsWaitingForATransferToOccur:"Current Contract awaiting transfer",
	  		BeneficiaryPassesResidencyValidationAtContractSignatureDate:"Bene Residency passed at Contract Signature Date",
	  		BeneficiaryPassesDtcEligibilityValidationAtContractSignatureDate:"Bene DTC eligible at Contract Signature Date",
	  		BeneficiarySinIsUsableAtContractSignatureDate:"Bene SIN usable at Contract Signature Date",
	  		HoldersSinIsUsableAtContractSignatureDate:"Holder SIN usable at Contract Signature Date",
	  		RemainingBalanceOnContract:"Remaining Balance on Contract ",
	  		CurrentReasonForChangeOfContractStatus:"Current Reason for Contract Status Change",
	  		CurrentTransferStatus:"Current Transfer Status",
	  		CurrentResidencyEligibilityOfBeneficiary:"Current Residency eligibility of bene",
	  		CurrentDtcEligibilityOfBeneficiary:"Current DTC eligibility of bene",
	  		CurrentBeneficiarySinUsability:"Current Bene SIN usability",
	  		CurrentHoldersSinUsability:"Current Holder SIN Usability",
	  		ContractRegistrationRetirementSavingsRolloverCompliant:"RSP R/O Compliant",
			ContractRegistrationEducationSavingsRolloverCompliant:"RESP R/O Compliant"
	}
}
}