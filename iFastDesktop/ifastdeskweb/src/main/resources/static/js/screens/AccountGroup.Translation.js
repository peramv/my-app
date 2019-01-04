/*********************************************************************************************
 * @file	AccountGroup.Translation.js
 * @author	Narin Suanlamyai
 * @desc	Translation JS file for Account Group screen
 *********************************************************************************************/
/*
 *	Navigate:	System Level: Menu > System Maintenance > Account Group
 *				
 *  History : 
 *
 *  23 Jul 2014 Narin S. P0233553 T55642
 *					- Created.
 *
 *  03 Sept 2014 Narin S. P0233553 T55678
 *					- Add validation for account group and linked account.
 *
 *  18 Sept 2014 Narin S. P0233553 DFT0041280 T55739
 *					- Add/Update error message for stop date field.
 *
 *	02 Oct 2014 Narin S. P0233553 DFT0041999 T55823
 *					- Effective Date cannot be future date of Account Group and Linked Account.
 *
 *  23 Sep. 2016 Winnie Cheng. P0256381 T83741 CHG0045765 Fund Broker Linkage for Germany
 *					- adding two lines for "Other Reference Number", no French translation, 
 *					- same as English
 *
 *  20 Oct 2016 Winnie Cheng. P0256381  T84056 CHG0045765 Fund Broker Linkage for Germany
 *                  - Adding duplication validation in popUp stage
 *                  
 *  14 Nov 2017 Sreejith A. P0266789-1523 Desktop changes for Account Linkage
 *  				- Error message for group id numeric validation 
 */
 
DesktopWeb.ScreenTranslation = {
	'enUS': {
		AccountGroup: "Account Group"
		,AccountNumber: "Account Number"
		,GroupType: "Group Type"
		,SearchFor: "Search For"
		,Active: "Active"
		,ShareholderName: "Shareholder Name"
		,GroupID: "Group ID"
		,GroupDesc: "Description"
		,DlrOwnerShipNumber: "Dlr Ownership#"
		,SearchResult: "Search Result"
		,LinkedAccount: "Linked Account"
		,ERR_DEFF_CANNOT_LESS_THAN_CURBUSDATE: "Effective Date cannot be less than current business date."
		,ERR_DEFF_CANNOT_FUTUREDATE: "Effective Date cannot be future date."
		,ERR_STOPDATE_CANNOT_LESS_THAN_CURBUSDATE: "Stop Date cannot be less than current business date."
		,ERR_STOPDATE_CANNOT_MORE_THAN_CURBUSDATE: "Stop Date cannot be greater than current business date."
		,ERR_STOPDATE_CANNOT_LESS_THAN_DEFF: "Stop Date cannot be less than Effective Date."
		,ERR_ACCT_DEFF_CANNOT_LESS_THAN_GRP_DEFF: "Effective Date of linked account cannot be less than Effective Date of Account Group."
		,ERR_ACCT_DEFF_CANNOT_MORE_THAN_GRP_STOPDATE: "Effective Date of linked account cannot be greater than Stop Date of Account Group."
		,ERR_ACCT_STOPDATE_CANNOT_MORE_THAN_GRP_STOPDATE: "Stop Date of linked account cannot be greater than Stop Date of Account Group."
		,ERR_STOPDATE_CANNOT_FUTUREDATE: "Stop Date cannot be future date."
		,WRN_CONTINUE: "Do you want to proceed?"
		,FIELD_IS_REQUIRED: "This is a required field."
		,GrpStat: "Status"
		,GrpRemark: "Remark"
		,PrimaryAcct: "Primary"
		,OtherReferenceNumberGrid: 'Other Ref.Num'
		,OtherReferenceNumberPopUp: 'Other Reference Number'
		,ERR_DUPLICATED_ACCTGRP: 'This account group already exists.'
		,ERR_DUPLICATED_ACCTGRPDESC: 'This account group description already exists.'
		,ERR_DUPLICATED_ACCTGRPMEMBER: 'Account Group Member record already exists or record overlap.'
		,NUMERIC_VALUE_ALLOWED: 'Only numeric values allowed'
	}
	
	,'frCA': {
		AccountGroup: "Account Group"
		,AccountNumber: "Account Number"
		,GroupType: "Group Type"
		,SearchFor: "Search For"
		,Active: "Active"
		,ShareholderName: "Shareholder Name"
		,GroupID: "Group ID"
		,GroupDesc: "Description"
		,DlrOwnerShipNumber: "Dlr Ownership#"
		,SearchResult: "Search Result"
		,LinkedAccount: "Linked Account"
		,ERR_DEFF_CANNOT_LESS_THAN_CURBUSDATE: "Effective Date cannot be less than current business date."
		,ERR_DEFF_CANNOT_FUTUREDATE: "Effective Date cannot be future date."
		,ERR_STOPDATE_CANNOT_LESS_THAN_CURBUSDATE: "Stop Date cannot be less than current business date."
		,ERR_STOPDATE_CANNOT_MORE_THAN_CURBUSDATE: "Stop Date cannot be greater than current business date."
		,ERR_STOPDATE_CANNOT_LESS_THAN_DEFF: "Stop Date cannot be less than Effective Date."
		,ERR_ACCT_DEFF_CANNOT_LESS_THAN_GRP_DEFF: "Effective Date of linked account cannot be less than Effective Date of Account Group."
		,ERR_ACCT_DEFF_CANNOT_MORE_THAN_GRP_STOPDATE: "Effective Date of linked account cannot be greater than Stop Date of Account Group."
		,ERR_ACCT_STOPDATE_CANNOT_MORE_THAN_GRP_STOPDATE: "Stop Date of linked account cannot be greater than Stop Date of Account Group."
		,ERR_STOPDATE_CANNOT_FUTUREDATE: "Stop Date cannot be future date."
		,WRN_CONTINUE: "Do you want to proceed?"
		,FIELD_IS_REQUIRED: "Il s'agit d'un champ obligatoire"
		,GrpStat: "Statut"
		,GrpRemark: "Remarques"
		,PrimaryAcct: "Principal"
		,OtherReferenceNumberGrid: 'Other Ref.Num'
		,OtherReferenceNumberPopUp: 'Other Reference Number'
		,ERR_DUPLICATED_ACCTGRP: 'This account group already exists.'
		,ERR_DUPLICATED_ACCTGRPDESC: 'This account group description already exists.'
		,ERR_DUPLICATED_ACCTGRPMEMBER: 'Account Group Member record already exists or record overlap.'
		,NUMERIC_VALUE_ALLOWED: 'Only numeric values allowed'
	}
}