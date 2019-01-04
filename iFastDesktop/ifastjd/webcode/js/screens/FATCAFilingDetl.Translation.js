/*********************************************************************************************
 * @file	FATCAFilingDetl.Translation.js
 * @author	Pannarasi Wongpakdee
 * @desc	Translation JS file for FATCA Filing Detail screen
 *********************************************************************************************/
/*
 *	Navigate:	System Level: Menu > System Maintenance > FATCA Filing Detail
 *				
 *  History : 
 *
 *  24 Dec 2014 P. Wongpakdee P0205605 T80214
 *					- Created.
 *
 *	05 Feb 2015 P. Wongpakdee P0205605 T80264
 *					- Adjustment section
 *
 *	08 Jan 2016 A. Mongkonrat P0241558 T81995 DFT0058373
 *					- Add Country Of Domicile translation.
 *
 *  04 Feb 2016 Aurkarn M. P0241558 T82184 DFT0059364 FATCA Reporting Enhancement
 *					- Fix typo from Silp to Slip
 *
 *	10 Jan 2017 Matira T. P0259672 T84599 CRS Enhancement Phase2
 *					- Add RFI Domicile and EntityType
 *
 */
							
DesktopWeb.ScreenTranslation = {
	'enUS': {
		SearchTitle: "Search"
		,SubmissionTitle: "Submission Level:"
		,ReportingTitle: "Reporting Unit level:"
		,SlipTitle: "Slip Level:"
		,AccountTitle: "Account Level:"
		,Regulation: "Regulation"
		,TaxYear: "Tax Year"
		,MsgIDSrch: "Message ID"
		,DocumentRefID: "Document Ref. ID"
		,SlipID: "Slip ID"
		,AsOfDate: "As of Date"
        ,CountryOfDomicile: "Country of Domicile"
		,TPSEffDate: "TPS Eff. Date"
		,SubmissionType: "Submission Type"
		,RunMode: "Run Mode"
		,ReportFile: "Report File"
		,RunDate: "Run Date"
		,MsgStatus: "Message Status"
		,RptUnitLevel: "Rpt. Unit<br/>Level"
		,RptUnitName: "Rpt. Unit<br/>Name"
		,RptUnitNameAdj: "Reporting Unit/FFI Name"
		,RptUnit: "Reporting Unit"
		,MsgID: "Message<br/>ID"
		,GovTaxAgency: "File<br/>Format"
		,NumOfRFFI: "No. of<br/>RFFIs"	
		,ReportingFFI: "Reporting FFI"
		,DocRefID: "Doc.<br/>Ref ID"
		,CorrectedDocRefID: "Corrected<br/>Doc. Ref ID"
		,NumOfSlip: "No. of<br/>Slips"	
		,NumOfSlipWarnErr: "No. of Slips<br/>w/Error"
		,FileStatus: "File Status"
		,AccountNum: "Account Number"
		,AccountNumReq: "Account"
		,EntityName: "Entity Name"
		,EntityName2: "Account Owner Name"
		,SlipID: "Slip ID"
		,CorrectedSlipID: "Corrected Slip ID"
		,SlipType: "Slip Type"
		,SlipType2: "Submission Type"
		,AdjustmentBtn: "Adjustment"
		,DetailBtn: "Detail"
		,GenOutput: "Generate Output"
		,FilingReq: "Filing Request"
		,AdjustmentReq: "Adjustment Request"
		,AccountReq: "Account Request"
		,SlipFullView: "Slip Level Full View"
        ,ReportingFFIChange: "Reporting FFI Change"
		,ErrorOnly: "Error Only"
		,ERR_TAXYEAR_NOT_SAME_YEAROFASOFDATE: "Tax Year should be the same year of As Of Date."
		,ERR_REPORTUNIT_IS_REQUIRED: "Reporting Unit is required."
		,ERR_AT_REPORTING_UNIT_LEVEL: "Error at Reporting Unit Level."
		,ERR_AT_SLIP_LEVEL: "Error at Slip Level."
		,ERR_REPORTUNIT_IS_STOPPED: "There is no effective Reporting Unit as per selected As of Date."
        ,ERR_TAXYEAR_GREATER_THAN_SYSTEM_TAXYEAR: "Tax year is greater than system tax year."
        ,ERR_MIXING_SUBMISSION_TYPE: "Mixing Submission Types is not allowed."
        ,RFIDomicile: "RFI Domicile"
		,EntityType: "Entity Type"
	}
	
	,'frCA': {
		SearchTitle: "Search"
		,SubmissionTitle: "Submission Level:"
		,ReportingTitle: "Reporting Unit level:"
		,SlipTitle: "Slip Level:"
		,AccountTitle: "Account Level:"
		,Regulation: "Regulation"
		,TaxYear: "Tax Year"
		,MsgIDSrch: "Message ID"
		,DocumentRefID: "Document Ref. ID"
		,SlipID: "Slip ID"
		,AsOfDate: "As of Date"
        ,CountryOfDomicile: "Country of Domicile"
		,TPSEffDate: "TPS Eff. Date"
		,SubmissionType: "Submission Type"
		,RunMode: "Run Mode"
		,ReportFile: "Report File"
		,RunDate: "Run Date"
		,MsgStatus: "Message Status"
		,RptUnitLevel: "Rpt. Unit<br/>Level"
		,RptUnitName: "Rpt. Unit<br/>Name"
		,RptUnitNameAdj: "Reporting Unit/FFI Name"
		,RptUnit: "Reporting Unit"
		,MsgID: "Message<br/>ID"
		,GovTaxAgency: "File<br/>Format"
		,NumOfRFFI: "No. of<br/>RFFIs"	
		,ReportingFFI: "Reporting FFI"
		,DocRefID: "Doc.<br/>Ref ID"
		,CorrectedDocRefID: "Corrected<br/>Doc. Ref ID"
		,NumOfSlip: "No. of<br/>Slips"	
		,NumOfSlipWarnErr: "No. of Slips<br/>w/Error"
		,FileStatus: "File Status"
		,AccountNum: "Account Number"
		,AccountNumReq: "Account"
		,EntityName: "Entity Name"
		,EntityName2: "Account Owner Name"
		,SlipID: "Slip ID"
		,CorrectedSlipID: "Corrected Slip ID"
		,SlipType: "Slip Type"
		,SlipType2: "Submission Type"
		,AdjustmentBtn: "Adjustment"
		,DetailBtn: "Detail"
		,GenOutput: "Generate Output"
		,FilingReq: "Filing Request"
		,AdjustmentReq: "Adjustment Request"
		,AccountReq: "Account Request"
		,SlipFullView: "Slip Level Full View"
        ,ReportingFFIChange: "Reporting FFI Change"
		,ErrorOnly: "Error Only"
		,ERR_TAXYEAR_NOT_SAME_YEAROFASOFDATE: "Tax Year should be the same year of As Of Date."
		,ERR_REPORTUNIT_IS_REQUIRED: "Reporting Unit is required."
		,ERR_AT_REPORTING_UNIT_LEVEL: "Error at Reporting Unit Level."
		,ERR_AT_SLIP_LEVEL: "Error at Slip Level."	
		,ERR_REPORTUNIT_IS_STOPPED: "There is no effective Reporting Unit as per selected As of Date."	
        ,ERR_TAXYEAR_GREATER_THAN_SYSTEM_TAXYEAR: "Tax year is greater than system tax year."       
        ,ERR_MIXING_SUBMISSION_TYPE: "Mixing Submission Types is not allowed."        
        ,RFIDomicile: "RFI Domicile"
		,EntityType: "Entity Type"
	}
}
