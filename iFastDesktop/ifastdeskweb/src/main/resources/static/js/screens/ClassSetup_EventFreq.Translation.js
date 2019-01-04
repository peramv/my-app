/*********************************************************************************************
 * @file	ClassSetup_EventFreq.Translation.js
 * @author 	Narin Suanlamyai
 * @desc	Translation file for Event Schedule Setup screen, part of Class Setup flow
 *********************************************************************************************/
/*
 * Procedure: ClassSetup_EventFreq.Translation.js
 *
 * Purpose  : Translation filed for Event Schedule screen under Fund Class Maintenance Screens
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Event Schedule screen
 *
 * History  :  
 *		15 Jul 2013 N. Suanlamyai P0214690 IN3362823 T53827
 *					- Add frCA section with English for displaying the screen in French.
 *
 *    05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *    20 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030808 T54932 
 *             - Modify the incorrect French Word
 *
 *  30 July 2014 Winnie Cheng P0232644 FN01 T78216
 *             - A new field added from Event Schedule screen for AIFMD enhancement
 *             
 *  09 Nov 2018 Winnie C. R19.2
 *  		P0278169-69 Project Spring:SSII-7422 PIMCO DCCS Trading 
 *			Adding NSCC offset field label
 */
 
DesktopWeb.ScreenTranslation = {
	'enUS': {
		FundGroupCode: "Fund Group Code"
		,FundList: "Fund List"
		,List: "List"
		,Description: "Description"
		,BusinessDayCode: "Business Day Code"
		,HolidayCode: "Holiday Code"
		,SettlementHolidayCode: "Settlement Holiday Code"
		,AdditionalDayListCode: "Additional Day List Code"
		,StlCurHldy: "Stl. Cur. Holiday Code"
		,Frequency: "Frequency"
		,ValuationSchedule: "Valuation Schedule"
		,CrystalisationSchedule: "PF Crystalisation Schedule"
		,DealingSchedule: "Dealing Schedule"
		,CutOffTime: "Cut Off Time"
		,FundGroupLevel: "Fund Group Level"
		,Timezone: "Time Zone"
		,ClientLevel: "Client Level"
		,AggregationLevel: "Aggregation Level"
		,MarketLevel: "Market Level"
		,NSCCOffset: "NSCC Offset (mins)"
		,Validate: "Validate"
		,DividendSchedule: "Dividend Schedule"
		,DividendFrequency: "Dividend Frequency"
		,CrystalisationFrequency: "PF Crystalisation Frequency"
		,TransType: "Trans Type"
		,SelectFundGroup: "Select a Fund Group"
		,EnterNewFundGroupDesc: "Fund Group Description"
		,EnterNewFundGroup: "Enter New Group"
		,HHMM: "HH:MM"
		,ReturntoSummary: "Return to Summary"
		,AddNewFundGrp: "Add New Group"
		,FundClassList: "Fund Classes List"
		,ValuationFundGroup: "Valuation Fund Group"
		,DividendFundGroup: "Dividend Fund Group"
		,Name: "Name"
		,RequiredAtLeastOne: "Please select at least one item."
		,requiredFieldErrMsg: "This is a required field."
		,InvalidTimeFormat: "Invalid time format. (HH:MM)"
		,ValuationInvalidNSCCOffset: "NSCC Offset time must be in range of -1439 to 1439."
		,RequiredDealingSchedule: "No Dealing Schedule entered."
		,RequiredAllTransTypes: "All transaction types need to be setup in dealing schedule."
		,ValuationInvalidFrequency: "Invalid Valuation frequency."
		,DividendFrequencyNotMatch: "Dividend frequency does not align with Valuation Schedule."
		,CrystalisationFrequencyNotMatch: "PF Crystalisation frequency does not align with Valuation Schedule."
		,DealingFrequencyNotMatch: "Dealing frequency does not align with Valuation Schedule."
		,ModifyValuationWarning: "Modification will impact all fund classes in the valuation fund group."
		,ModifyDividendWarning: "Modification will impact all fund classes in the dividend fund group."
		,ModifyValuationFreqWarning: "You have to specify the first start date for re-generate the schedule."
		,ModifyDividendFreqWarning: "You have to specify the first start date for re-generate the schedule."
		,RequiredValidateValuation: "Valuation Schedule needs to be validated."
		,DivFreqMoreThanValnFreq: "Dividend frequency cannot be less than Valuation frequency."
		,CryFreqMoreThanValnFreq: "PF Crystalisation frequency cannot be less than Valuation frequency."
		,DealFreqMoreThanValnFreq: "Dealing frequency cannot be less than Valuation frequency."
		,PassedValidate: "Valuation frequency is valid."
		,DividendFrequencyNotValid: "Dividend Frequency is not valid."
		,DealingFrequencyNotValid: "Dealing Frequency is not valid."
		,OnlyValid: "Only '%1%' is valid."
		,dealingFreqOn: "Dealing Frequency On"
		,dealingFreqType: "Dealing Frequency Type"
		,dealingFreqDay:  "Dealing Frequency Day"
		,dealingFreqMonth: "Dealing Frequency Month"
		,dealingFreqEndOf: "Dealing Frequency EndOf"
		,dividendFreqOn: "Dividend Frequency On"
		,dividendFreqType: "Dividend Frequency Type"
		,dividendFreqDay: "Dividend Frequency Day"
		,dividendFreqMonth: "Dividend Frequency Month"
		,dividendFreqEndOf: "Dividend Frequency EndOf"
		,PFFreqOn: "PF Crystalisation Frequency On"
		,PFFreqType: "PF Crystalisation Frequency Type"
		,PFFreqDay: "PF Crystalisation Frequency Day"
		,PFFreqMonth: "PF Crystalisation Frequency Month"
		,PFFreqEndOf: "PF Crystalisation Frequency EndOf"
		,RedemptionDealingFreq: "Redemption Dealing Freq."

	}	
	,'frCA': {
		FundGroupCode: "Code du groupe de fonds"
		,FundList: "Liste de fonds"
		,List: "Liste"
		,Description: "Description"
		,BusinessDayCode: "Code du jour ouvrable"
		,HolidayCode: "Code de jour férié"
		,SettlementHolidayCode: "Code de règlement de jour férié"
		,AdditionalDayListCode: "Code de la liste de jours additionnels"
		,StlCurHldy: "Code de jour férié cour. stl."
		,Frequency: "Fréquence"
		,ValuationSchedule: "Échéancier d'évaluation"
		,CrystalisationSchedule: "Barème de la cristallisation des FR"
		,DealingSchedule: "Échéancier de transactions"
		,CutOffTime:"Date de clôture"
		,FundGroupLevel: "Niveau du groupe de fonds"
		,NSCCOffset: "NSC Délai (minutes)"
		,Timezone: "Fuseau horaire"
		,ClientLevel: "Niveau du client"
		,AggregationLevel: "Niveau de regroupement"
		,MarketLevel: "Niveau du marché"
		,Validate: "Valider"
		,DividendSchedule: "Échéancier de dividendes"
		,DividendFrequency: "Fréquence des dividendes"
		,CrystalisationFrequency: "Fréquence de cristallisation des FR"
		,TransType: "Type de transaction"
		,SelectFundGroup: "Sélectionnez un groupe de Fonds"
		,EnterNewFundGroupDesc: "Description du groupe de fonds"
		,EnterNewFundGroup: "Entrer un nouveau groupe"
		,HHMM: "HH h MM"
		,ReturntoSummary: "Retour au sommaire"
		,AddNewFundGrp: "Ajouter un nouveau groupe"
		,FundClassList: "Liste des catégories de fonds"
		,ValuationFundGroup: "Groupe de fonds d'évaluation"
		,DividendFundGroup: "Groupe de fonds de dividendes"
		,Name: "Nom"
		,RequiredAtLeastOne: "Veuillez sélectionner au moins un article."
		,requiredFieldErrMsg: "Il s'agit d'un champ obligatoire"
		,InvalidTimeFormat: "Format de la date non valable (HH h MM)"
		,RequiredDealingSchedule: "Aucun échéancier de transaction entré"
		,RequiredAllTransTypes: "Tous les types de transactions doivent être créés selon l'échéancier de transactions"
		,ValuationInvalidFrequency: "Fréquence d'évaluation non valable"
		,ValuationInvalidNSCCOffset: "L'heure de compensation doit être dans la plage entre -1439 et 1439."
		,DividendFrequencyNotMatch: "La fréquence des dividendes n'est pas conforme à l'échéancier d'évaluation"
		,CrystalisationFrequencyNotMatch: "La fréquence de la cristallisation des FR n'est pas conforme à  l'échéancier d'évaluation."
		,DealingFrequencyNotMatch: "La fréquence des transactions n'est pas conforme à l’échéancier des évaluations"
		,ModifyValuationWarning: "La modification aura un effet sur toutes les catégories d'actif dans le groupe de fonds d’évaluation."
		,ModifyDividendWarning: "La modification aura un effet sur toutes les catégories de fonds dans le groupe des fonds à dividendes"
		,ModifyValuationFreqWarning: "Vous devez préciser la première date de début pour générer l'échéancier à nouveau."
		,ModifyDividendFreqWarning: "Vous devez préciser la première date de début pour générer l'échéancier à nouveau."
		,RequiredValidateValuation: "L'échéancier d'évaluation doit être validé."
		,DivFreqMoreThanValnFreq: "La fréquence des dividendes ne peut être inférieure à la fréquence d'évaluation"
		,CryFreqMoreThanValnFreq: "La fréquence de la cristallisation des FR ne peut être inférieure à la fréquence d'évaluation."
		,DealFreqMoreThanValnFreq: "La fréquence des transactions ne peut être inférieure à la fréquence d'évaluation"
		,PassedValidate: "La fréquence de validation est valable"
		,DividendFrequencyNotValid: "La fréquence des dividendes n'est pas valable"
		,DealingFrequencyNotValid: "La fréquence des transactions n'est pas valable"
		,OnlyValid: "Seulement '%1%' est valable."
		,dealingFreqOn: "Fréquence des transactions (date)"
		,dealingFreqType: "Type de fréquence de transactions"
		,dealingFreqDay:  "Fréquence des transactions (jour)"
		,dealingFreqMonth: "Fréquence des transactions (mois)"
		,dealingFreqEndOf: "Fréquence des transactions (fin)"
		,dividendFreqOn: "Fréquence des dividendes (date)"
		,dividendFreqType: "Fréquence des dividendes (type)"
		,dividendFreqDay: "Fréquence des dividendes (jour)"
		,dividendFreqMonth: "Fréquence des dividendes (mois)"
		,dividendFreqEndOf: "Fréquence des dividendes (fin)"
		,PFFreqOn: "Fréquence de la cristallisation des FR (date)"
		,PFFreqType: "Type de la fréquence de cristallisation des FR"
		,PFFreqDay: "Jour de fréquence de la cristallisation des FR"
		,PFFreqMonth: "Fréquence de la cristallisation des FR (mois)"
		,PFFreqEndOf: "Fréquence de la cristallisation des FR (fin)"
		,RedemptionDealingFreq: "La fréquence de racha"
	}	
}
