/*********************************************************************************************
 * @file	ClassSetup_TradeDayCtrls.Translation.js
 * @author	
 * @desc	Translation JS file for ClassSetup TradeDay Controls screen.
 *********************************************************************************************/
 /*
 * History : 
 *
 *    05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *    20 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030808 T54932 
 *             - Modify the incorrect French Word
 *
 *	  21 May 2015 Winnie Cheng P0241128 T80810
 *			   - Added one field "Redemption Notice Period". 
 *
 * 	  8  Jan 2018 Sreejith A P0274727 P0274727-1
 *			- Added purchase payment lead days and
 *				  different settlement currency fields
 *
 *	  23 Jan 2018 Sreejith.A P0274733 P0274733-156
 *			 - Added MFR payment lead days
 *
 *	  22 Mar 2018 Sreejith.A P0274727 P0274727-88
 *			 - T+0 Project P0274727 changes revert from 18.3
 *
 *	  12 Jun 2018 Sreejith.A P0277704 P0277704-17
 *			- T+0 Project put back reverted changes for trade control and settle date control
 */
 
DesktopWeb.ScreenTranslation = {
	
	'enUS': {
		Purchase: "Purchase"
		,Redemption: "Redemption"
		,Exchange: "Exchange"
		,Transfer: "Transfer"
		,ExchangeIn: "Exchange In"
		,ExchangeOut: "Exchange Out"
		,TradeLeadDays: "Trade Lead Days"		
		,LastDividendDate: "Last Dividend Date"
		,LastSettleDate: "Last Settle Date"
		,LastCycleDate: "Last Cycle Date"
		,NextSettleDate: "Next Settle Date"
		,NextCycleDate: "Next Cycle Date"
		,LastValuationDate: "Last Valuation Date"
		,NextValuationDate: "Next Valuation Date"
		,LastMgmtFeeDate: "Last Mgmt. Fee Date"
		,LastMgmtFeeRebateDate: "Last Mgmt. Fee Rebate Date"
		,LastCrystalisationDate: "Last PF Crystalisation Date"
		,NAVCalcDays: "NAV Calc. Days"
		,PaymentLeadDays: "Payment Lead Days"
		,PurchasePaymentLeadDays: "Purchase Payment Lead Days"
		,TradeDayDelay: "Trade Day Delay"
		,AutoForceCancelDays: "Auto Force Cancel Days"
		,CutOffDays: "Cut Off Days"
		,InvalidTimeFormat: "Invalid Time Format"
		,HHMM: "HH:MM"
		,Day: "Day"
		,Days: "Days"
		,DayType: "Day Type"
		,Time: "Time"
		,DaysMoreThan3DigitsErrMsg: "The days cannot be more than 3 digits."
		,DaysMoreThan99WarningMsg: "You entered the days greater than 99. <br/><br/>Please verify you entered the valid data."
		,RequiredRedemptionCutOffTime: "Cut Off Time for redemption is required."
		,RequiredDayType: "Day Type is required."
		,Exceeds3Digits: "Exceeds 3 digits"
		,Miscellaneous: "Miscellaneous"
		,ReturntoSummary: "Return to Summary"
		,LastTFRDate: "Last Trailer Fee Rebate Date"
		,RedemptionNoticePeriod: "Redemption Notice Period"
		,UnitDays : "Unit:"
		,AmountDays : "Amount:"
		,AmountType : "All Amount Type"
		,DifferentSettleCurrency : "Different settlement currency"
		,MfrPymtLeadDays: "MFR Payment Lead Days"
	}
	
	,'frCA': {
		Purchase: "Achat"
		,Redemption: "Rachat"
		,Exchange: "Échange"
		,Transfer: "Transfert"
		,ExchangeIn: "Échange entrant"
		,ExchangeOut: "Échange sortant"
		,TradeLeadDays: "Délai de transaction en jours"
		,LastDividendDate: "Dernière date de dividende"
		,LastSettleDate: "Dernière date de règlement"
		,LastCycleDate: "Dernière date de cycle"
		,NextSettleDate: "Prochaine date de règlement"
		,NextCycleDate: "Prochaine date de cycle"
		,LastValuationDate: "Dernière date d'évaluation"
		,NextValuationDate: "Prochaine date d'évaluation"
		,LastMgmtFeeDate: "Dernière date de frais de gestion"
		,LastMgmtFeeRebateDate: 'Date de remise à jour des frais de gestion'
		,LastCrystalisationDate: "Date de dernière cristallisation des FR"
		,NAVCalcDays: "Jours de calcul de la valeur de l'actif net"
		,PaymentLeadDays: "Délai de paiement en jours"
		,PurchasePaymentLeadDays: "Délai de paiement de l’achat"
		,TradeDayDelay: "Retard des jours de transaction"
		,AutoForceCancelDays: "Jours de suppression forcée automatique"
		,CutOffDays: "Jours limites"
		,InvalidTimeFormat: "Format de la date non valable"
		,HHMM: "HH h MM"
		,Day: "Jour"
		,Days: "Jours"
		,DayType: "Type de jour"
		,Time: "Heure"
		,DaysMoreThan3DigitsErrMsg: "Les jours ne peuvent pas compter plus de trois chiffres."
		,DaysMoreThan99WarningMsg: "Vous avez entré une valeur pour les jours supérieure à 99. <br/><br/>Veuillez vérifier que vous avez entré une donnée valable."
		,RequiredRedemptionCutOffTime: "La date de clôture est demandée pour le rachat"
		,RequiredDayType: "Le type de jour est requis"
		,Exceeds3Digits: "Plus que 3 chiffres"
		,Miscellaneous: "Divers"
		,ReturntoSummary: "Retour au sommaire"
		,LastTFRDate: "Last Trailer Fee Rebate Date"
		,RedemptionNoticePeriod: "Préavis de rachat"
		,UnitDays : "Unité:"
		,AmountDays : "Montant:"
		,AmountType : "Tous les types de montant"
		,DifferentSettleCurrency : "Devise de règlement différente"
		,MfrPymtLeadDays: "Jours principaux du paiement du RFG"
	}
}