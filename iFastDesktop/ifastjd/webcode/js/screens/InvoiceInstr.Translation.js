/*
 * Procedure: InvoiceInstr.Translation.js
 *
 * Purpose  : Invoice Instruction screens manage invoice information data			  
 *             
 * Notes    : Open screens by Menu -> MF and MFR Maintenance -> Invoice Instruction
 *							  Menu -> System Maintenance -> Holding Company -> Invoice Instructions
 *
 * History  : 
 *	
 *		5 Mar 2013 Supareuk Sukjaitham PETP0206635 FN01 MFR MFI Enhancments
 *			- Created
 *
 *		2 May 2013 Supareuk Sukjaitham PETP0206635 FN01 IN3318278
 *			- Added new translation for Term of payment	
 *
 *		27 May 2013 Pannarasi Wongpakdee PETP0206635 FN01 T53618 IN3336672
 *			- Combined the warning message to Error_WarningChangedDate
 *
 */

DesktopWeb.ScreenTranslation = {	
	'enUS': {
		HoldingCompany: "Holding Company"
		,Invoice: "Invoice"
		,InvoiceId: "Invoice ID"
		,InvoiceName: "Name"
		,InvoiceLabel: "Invoice ID/Name"
		,EffectiveAsOf: "Effective As Of"
		,Frequency: "Frequency"
		,BillingEntityTitle: "Billing Entity"
		,DeliveryName: "Delivery Name"
		,DeliveryName2: "Delivery Name 2"
		,InvoiceName1: "Invoice Name"
		,InvoiceName2: "Invoice Name 2"
		,Address: "Address"
		,City: "City"
		,Country: "Province/Country"
		,PSTL: "Postal/Zip Code"
		,BillingDetail: "Billing Details"
		,PaymentOption: "Payment Option"
		,TermOfPayment: "Term Of Payment"
		,Currency: "Currency"
		,TaxApply: "Tax Applies"
		,Language: "Language"
		,SupplementReq: "Supplement Required"
		,BrandingType: "Branding Type"
		,InvoiceInformation: "Invoice Information"
		,InvoiceInstr: "Invoice Instruction"
		,InvoiceInstrDetl: "Invoice Instruction Detail"
		,InvoiceInstrMaintenance: "Invoice Instruction Maintenance"
		,AccountList: "Account List"
		,Termdays: "Term Days"
		,TermdaysType: "Term Days Type"
		
		,Error_EitherHoldComOrInvoiceInstr:"Holding Company or Invoice ID/Name must be entered."
		,Error_EffectiveDateRequire:"Effective Date must be entered"
		,Error_StartDateNotPriorEndDate: "End Date cannot be prior to Start Date"		
		,Error_StartDateOrEndDateIsBlank: "Start Date or End Date must be entered"
		,Error_WarningChangedDate: "There is an account linked to the Invoice Instruction ID. Changes to the effective and/or stop date will not be applied to the linked account."
	}
	,'frCA': {
		HoldingCompany: "Holding Company"
		,Invoice: "Invoice"
		,InvoiceId: "Invoice ID"
		,InvoiceName: "Name"
		,InvoiceLabel: "Invoice ID/Name"
		,EffectiveAsOf: "Effective As Of"
		,Frequency: "Frequency"
		,BillingEntityTitle: "Billing Entity"
		,DeliveryName: "Delivery Name"
		,DeliveryName2: "Delivery Name 2"
		,InvoiceName1: "Invoice Name"
		,InvoiceName2: "Invoice Name 2"
		,Address: "Address"
		,City: "City"
		,Country: "Province/Country"
		,PSTL: "Postal/Zip Code"
		,BillingDetail: "Billing Details"
		,PaymentOption: "Payment Option"
		,TermOfPayment: "Term Of Payment"
		,Currency: "Currency"
		,TaxApply: "Tax Applies"
		,Language: "Language"
		,SupplementReq: "Supplement Required"
		,BrandingType: "Branding Type"
		,InvoiceInformation: "Invoice Information"
		,InvoiceInstr: "Invoice Instruction"
		,InvoiceInstrDetl: "Invoice Instruction Detail"
		,InvoiceInstrMaintenance: "Invoice Instruction Maintenance"
		,AccountList: "Account List"
		,Termdays: "Term Days"
		,TermdaysType: "Term Days Type"
		
		,Error_EitherHoldComOrInvoiceInstr:"Holding Company or Invoice ID/Name must be entered."
		,Error_EffectiveDateRequire:"Effective Date must be entered"
		,Error_StartDateNotPriorEndDate: "End Date cannot be prior to Start Date"		
		,Error_StartDateOrEndDateIsBlank: "Start Date or End Date must be entered"
		,Error_WarningChangedDate: "There is an account linked to the Invoice Instruction ID. Changes to the effective and/or stop date will not be applied to the linked account."
	}
}