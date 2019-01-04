/*********************************************************************************************
 * @file	ClassSetup_FeeConfig.Translation.js
 * @author	
 * @desc	Translation JS file for ClassSetup Fee Configuration screen.
 *********************************************************************************************/
/*
 * Procedure: ClassSetup_FeeConfig.Translation.js
 *
 * Purpose  : Fee Configuration screens under Class Maintenance Screens
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Fee Configuration screens
 *
 * History  : 
 *
 *		25 Nov 2012 H.Sartsangchan P0205419 FN01 MF/MFR Enhancement
 *					- Change old translation for broker and brokercharge to brokerpotion and brokerchange
 *					- Add new 3 translation 
 *
 *    05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French
 *
 *    24 March 2015 P0181067 T80539 DFT0045635 FundFeeConfig setup for Advisor Fee 
 *             - Move Management Fee, Management Fee Rebate and Advisor Fee from Fee Configuration to Fee Model Configuration. 
 */
DesktopWeb.ScreenTranslation = {
	
	"enUS": {
		TrailerFeeDate: "Trailer Fee Date"
		,TrailerFeeGrandFatherDate: "Trailer Fee GrandFather Date"
		,EarlyMaturityDays: "Early Maturity Days"
		,ShortTermTradingMaturityDays: "Short-Term Trading Maturity Days"
		,Applicable: "Applicable"		
		,FeeType: "Fee Type"
		,BasedOn: "Based On"
		,Paid: "Paid"
		,BrokerCommision: "Broker Commission"
		,DSCBasedRate: "DSC Based Rate"
		,MinVarDSC: "Min. Var DSC"
		,DSCOverride: "DSC Override"		
		,AcquisitionFeeType: "Acquisition Fee Type"
		,AcquisitionRate: "Acquisition Rate"
		,MaxFeeRate: "Max. Fee Rate"
		,WithholdRate: "Withhold Rate"
		,AcquisitionPaid: "Acquisition Paid"
		,AcquisitionBasedOn: "Acquisition Based On"
		,MinFeeRate: "Min. Fee Rate"
		,EighthAnnivDeMinimusOption: "8th Anniv. De-Minimus Option"
		,MFRPaidBy: "MFR Paid By"
		,FirstDeemedDisposalDate: "1st Deemed Disposal Date"
		,SecondDeemedDisposalDate: "2nd Deemed Disposal Date"
		,FeeCode: "Fee Code"		
		,FeeScale: "Fee Scale"
		,TrailerFees: "Trailer Fees"
		,MaturityDays: "Maturity Days"
		,TransferFee: "Transfer Fee"
		,TrailerFeeRebate: "Trailer Fee Rebate"
		,FrontEndLoad: "Front End Load"
		,BackEndLoad: "Back End Load"
		,FeeScales: "Fee Scales"
		,IWTFee: "IWT Fee"
		,ReturntoSummary: "Return to Summary"
		,PerfFeeConfig: "Performance Fee"
		,RedirectMsg: "You have changed this Fund/Class to applicable the Performance Fee. <br/><br/> Do you want to setup the Performance Fee now? <br/>"
		,Error_NoFeeScale :"No fee scales entered"
	}
	
	,'frCA': {
		TrailerFeeDate: "Date de frais administratifs"
		,TrailerFeeGrandFatherDate: "Date bénéficiant d'une clause de droits acquis dee frais administratifs"
		,EarlyMaturityDays: "Date d'échéance anticipée"
		,ShortTermTradingMaturityDays: "Jours d'échéance de l'opération à court terme"
		,Applicable: "Applicable"
		,FeeType: "Type de frais"
		,BasedOn: "Fondés sur"
		,Paid: "Payés"
		,BrokerCommision: "Commission du courtier"
		,DSCBasedRate: "Taux basé sur les FAR"
		,MinVarDSC: "FAR avec variation minimale"
		,DSCOverride: "Modification des FAR"
		,AcquisitionFeeType: "Type de frais d'acquisition"
		,AcquisitionRate: "Taux d'acquisition"
		,MaxFeeRate: "Taux de commission maximal"
		,WithholdRate: "Taux de retenue"
		,AcquisitionPaid: "Acquisition payée"
		,AcquisitionBasedOn: "Acquisition fondée sur"
		,MinFeeRate: "Taux de commission minimal"
		,EighthAnnivDeMinimusOption: "Date d'exemption de frais de 8e anniversaire"
		,MFRPaidBy: "Taux de commission minimal payé par"
		,FirstDeemedDisposalDate: "Première date de dispostion réputée"
		,SecondDeemedDisposalDate: "Deuxième date de dispostion réputée"
		,FeeCode: "Code de frais"
		,FeeScale: "Échelle de frais"
		,TrailerFees: "Frais administratifs"
		,MaturityDays: "Jours d'échéance"
		,TransferFee: "Frais de transfert"
		,TrailerFeeRebate: "Remboursement Commission du Service"
		,FrontEndLoad: "Frais initiaux"
		,BackEndLoad: "Frais de rachat"
		,FeeScales: "Échelles de frais"
		,IWTFee: "Frais d'impôt de retenue d'intérêt"
		,ReturntoSummary: "Retour au sommaire"
		,PerfFeeConfig: "Frais liés au rendement"
		,RedirectMsg: "Vous avez changé ce Fonds/cette Catégorie pour les frais liés au rendement applicables. <br/><br/> Voulez-vous créer les frais liés au rendement maintenant?<br/>"
		,Error_NoFeeScale : "Aucun barème de frais entré"
	}
}