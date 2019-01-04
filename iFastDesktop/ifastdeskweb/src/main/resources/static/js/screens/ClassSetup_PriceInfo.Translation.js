/*********************************************************************************************
 * @file	ClassSetup_PriceInfo.Translation.js
 * @author	
 * @desc	Translation JS file for ClassSetup Price Information screen.
 *********************************************************************************************/
 /*
 * History : 
 *
 *    05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *  10 Dec 2015 Winnie Cheng P0248498 CHG0043235 T81863
 *          - Adding one dropdown field : capstock rate type
 *           
 *  30 Mar 2018 Winnie Cheng P0275379-35 MMFR R18.4
 *          - Adding validation for fixed Rate based on fixed price flag
 *
 *  23 July 2018 Winnie Cheng P0277183-158 Intraday Pricing R18.5
 *          - Allowing to set up intraday pricing set when applicable
 */
 
DesktopWeb.ScreenTranslation = {
	
	'enUS': {
		NAVCurrency: "NAV Currency"
		,CustomValuation: "Custom Valuation"
		,ESGPriceSuppress: "ESG Price Suppress"
		,FixedPrice: "Fixed Price"
		,FixedRate: "Fixed Rate"
		,FixedPrecision: "Precision Rate"
		,VarianceAmount: "Variance Amount"
		,VarianceType: "Variance Type"
		,LoadGroup: "Load Group"
		,CalculationMethod: "Calculation Method"
		,Precision: "Precision"
		,FractionalShares: "Fractional Shares"
		,AllocatedType: "Allocated Type"
		,ValidSettleCurrencies: "Valid Settle Currencies"		
		,NAV: "Pricing"
		,Units: "Units"		
		,GAVPricing: "GAV Pricing"
		,ReturntoSummary: "Return to Summary"	
		,RoundFlag: "Round Flag"
		,CapStockFXRateType: "Capstock Rate Type"
		,fixRateResetZero: "You are about to change the fixed price. The fixed rate will be set to zero."
		,fixRateRequired: "Fixed Rate must not be ZERO when fixed price is YES."
		,isInValidNumber: "is not a valid number."
		,HHMM: "HH:MM"
		,InvalidTimeFormat: "Invalid time format. (HH:MM)"
		,IntradayPricing: "Intraday Pricing"
		,PricePointActive: "Price Point Active"
		,EffectiveFrom: "Effective From"
		,EffectiveTo: "Effective To"
		,NumOfPoints: "# of Points"
		,PricePointTime: "Price Point Time"
		,PriceCode: "Price Code"
		,IDPrice: "ID Price"
		,PricePoint: "Price Point"
		,EffectiveFromLessTD: "Effective From cannot be less than current trade date + 1."
		,EffectiveToLessFrom: "Effective To date cannot be less than Effective From date."
		,EffectiveToLessTD: "Effective To date cannot be less than the trade date + 1."
		,AtLeastOnePricePoint: "At least one price point must be defined for a set."
		,OverlapPriceset: "The price set overlaps with an existing price set."
		,ValidateHours: "Hours must less or equal than 23."
		,ValidateMinutes: "Minutes must less or equal than 59."
		,ValFundCutOffTime: "The price point value cannot be greater or equal than fund cut-off value."
		,ValCurrPrevPrice: "The price point value cannot be equal or less or than previous price point value."
		,IsEmptyPricePoint: "A price point must have a value."
	}
	
	,'frCA': {
		NAVCurrency: "Monnaie de la valeur de l'actif net"
		,CustomValuation: "Évaluation personnalisée"
		,ESGPriceSuppress: "Suppression de prix ESG"
		,FixedPrice: "Prix fixe"
		,FixedRate: "Taux fixe"
		,FixedPrecision: "Précision fixe"
		,VarianceAmount: "Montant d'écart"
		,VarianceType: "Type d'écart"
		,LoadGroup: "Groupe de téléchargement"
		,CalculationMethod: "Méthode de calcul"
		,Precision: "Précision"
		,FractionalShares: "Parts fractionnelles"
		,AllocatedType: "Type de répartition"
		,ValidSettleCurrencies: "Monnaies de règlement valides"
		,NAV: "Valeur de l'actif net"
		,Units: "Unités"
		,GAVPricing: "Tarification VBA"
		,ReturntoSummary: "Retour au sommaire"
		,RoundFlag: "Drapeau rond"
		,CapStockFXRateType: "Capstock Type de tarif"
		,fixRateResetZero: "Vous êtes en train de changer le prix fixe. Le taux fixe sera mis à zéro."
		,fixRateRequired: "Le taux fixe ne peut être de ZÉRO lorsqu'il a été entré OUI pour le prix fixe."
		,isInValidNumber: "n'est pas un nombre valide."
		,HHMM: "HH h MM"
		,IntradayPricing: "Prix intrajournalier"
		,PricePointActive: "Prix actif"
		,EffectiveFrom: "Effectif à compter du"
		,EffectiveTo: "Effectif jusqu’au"
		,NumOfPoints: "Nombre de points"
		,PricePointTime: "Période active"
		,PriceCode: "Prix"
		,IDPrice: "Prix identifiant"
		,PricePoint: "Code de prix"
		,EffectiveFromLessTD: "La date d’effet ne peut commencer avant la date de transaction +1."
		,EffectiveToLessFrom: "La date d'effet ne peut se terminer avant de commencer."
		,EffectiveToLessTD: "La date d’effet ne peut se terminer avant la date de transaction +1."
		,AtLeastOnePricePoint: "Au moins une valeur doit être définie pour fixer un prix."
		,OverlapPriceset: "Le prix fixé chevauche un prix déterminé existant."
		,ValidateHours: "Le nombre d’heures doit être inférieur ou équivalent à 23."
		,ValidateMinutes: "Le nombre de minutes doit être inférieur ou égal à 59."
		,ValFundCutOffTime: "Le prix ne peut être supérieur ou égal à la valeur de clôture du fonds."
		,ValCurrPrevPrice: "Le prix ne peut être inférieur ou équivalent au prix précédent."
		,IsEmptyPricePoint: "Un prix doit avoir une valeur."
		,InvalidTimeFormat: "Format de la date non valable (HH h MM)."
	}
}