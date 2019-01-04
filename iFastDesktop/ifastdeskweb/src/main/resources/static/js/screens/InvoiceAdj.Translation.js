/**********************************************************************************************
 *
 * Procedure: InvoiceAdj.Translation.js
 *
 * Purpose  : Invoice Adjustment screen for adjusting the Payments of Invoice			  
 *
 * Notes	: Open screen by -> Invoice Instructions screen (Invoice Button) 
 *
 * History  : 
 *	
 *		5 Mar 2013 Pannarasi Wongpakdee PETP0206635 FN01 MFR MFI Enhancments
 *			- Created
 *
 *     19 Aug 2013  G. Thawornwachirakun PETP0206635 FN01 T54037 DFT0013578
 *          - Modify split comment from the number of character to split by enter
 * 
 **********************************************************************************************/
 
DesktopWeb.ScreenTranslation = 
{	
	'enUS': 
	{
		// All labels
		InvoiceAdj: "Invoice Adjustment"
		,OffsetAmount: "Offset Amount"
		,AdjmentDate: "Adjustment Date"
		,Comment: "Comment"
		,PaymentFor: "Payment For"
		,PaymentPeriod: "Payment Period"
		,PaymentDate: "Payment Date"
		,Amount: "Amount"
		,Currency: "Currency"
		,Status: "Status"
		,InvoiceId: "Invoice ID"
		,Username: "Username"
		,ModUser: "ModUser"
		,ProcessDate: "ProcessDate"
		,ModDate: "ModDate"
		
		// All buttons
		,AdjDetail: "Adjustment"
		,PrintIV: "Print Invoice"
		,Admin: "Admin"
		,More: "More"
		,Ok: "OK"
		,Cancel: "Cancel"
		
		// All messages
		,PromptMsg: "You have modified the screen - Do you want to discard them? <br/><br/><br/><br/>If you choose OK, all changes since your last confirmation will be wiped out. <br/>This action cannot be undone!"
		,Loading: "Loading ..."
		,Searching: "Searching ..."
		,Updating: "Updating ..."
		,Validating: "Validating ..."
		,OffSetAmtErr: "OffSet Amount should be 2 decimals (eg. 99.99)."
		,PrintMsg: "The Print Job Scheduler has been called; please check the job status on iFast Base."
		,AdjustError: "All fields cannot be blank; changes will not be submitted."
		,CommentError: "Not allowed to add comment more than 4 lines <br/>and the maximum characters of each line are 80."
	}
	
	,'frCA': 
	{
		// All labels
		InvoiceAdj: "Invoice Adjustment"
		,OffsetAmount: "Offset Amount"
		,AdjmentDate: "Adjustment Date"
		,Comment: "Comment"
		,PaymentFor: "Payment For"
		,PaymentPeriod: "Payment Period"
		,PaymentDate: "Payment Date"
		,Amount: "Amount"
		,Currency: "Currency"
		,Status: "Status"
		,InvoiceId: "Invoice ID"
		,Username: "Username"
		,ModUser: "ModUser"
		,ProcessDate: "ProcessDate"
		,ModDate: "ModDate"
		
		// All buttons
		,AdjDetail: "Adjustment"
		,PrintIV: "Print Invoice"
		,Admin: "Admin"
		,More: "More"
		,Ok: "OK"
		,Cancel: "Cancel"
		
		// All messages
		,PromptMsg: "You have modified the screen - Do you want to discard them? <br/><br/><br/><br/>If you choose OK, all changes since your last confirmation will be wiped out. <br/>This action cannot be undone!"
		,Loading: "Loading ..."
		,Searching: "Searching ..."
		,Updating: "Updating ..."
		,Validating: "Validating ..."
		,OffSetAmtErr: "OffSet Amount should be 2 decimals (eg. 99.99)."
		,PrintMsg: "The Print Job Scheduler has been called; please check the job status on iFast Base."
		,AdjustError: "All fields cannot be blank; changes will not be submitted."
		,CommentError: "Not allowed to add comment more than 4 lines <br/>and the maximum  characters of each line are 80."
	}
}