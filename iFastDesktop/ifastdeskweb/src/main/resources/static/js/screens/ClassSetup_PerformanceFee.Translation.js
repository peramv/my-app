/*********************************************************************************************
 * @file	ClassSetup_PerformanceFee.Translation.js
 * @author 	Narin Suanlamyai
 * @desc	Translation file for Performance Fee Configuration screen, part of Class Setup flow
 *********************************************************************************************/
/*
 * Procedure: ClassSetup_PerformanceFee.Translation.js
 *
 * Purpose  : Translation filed for Performance Fee screen under Fund Class Maintenance Screens
 *             
 * Notes    : Open screens by Menu -> Fund Level Maintenance -> Fund Class Maintenance -> Performance Fee screen
 *
 * History  :  
 *		15 Jul 2013 N. Suanlamyai P0214690 IN3362823 T53827
 *					- Add frCA section with English for displaying the screen in French.
 *
 *    05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 */

DesktopWeb.ScreenTranslation = {
	'enUS': {
		feeMethod: "Fee Method"
		,calcBasis: "Calculation Basis"
		,lossCarryForward: "Loss Carry Forward Option"
		,divAddBack: "Dividend Treatment Option"
		,lotRedMethod: "Default Lot Reduction Method"
		,perfFeeCalcPrecision: "Calculation Precision"
		,perfFeePrecision: "Performance Fee Precision"
		,gavRate: "Initial GAV"
		,classHWMRate: "Initial HWM Per Share"
		,classHWMResetDate: "Initial HWM Date"
		,hurdle: "Hurdle"
		,initValues: "Initial Values"
		,benchmarkType: "Benchmark Type"
		,fixRate: "Fix Rate"
		,benchmarkIndex: "Benchmark Index"
		,benchmarkAdjRate: "Benchmark Adjustment Rate"
		,daysBasis: "Day Basis"
		,weighting: "Weight"
		,ReturntoSummary: "Return to Summary"
		,weightingErrMsg: "Total of weighting must be 100%."
		,hurldeConfigErrMsg: "No hurdle configurations entered."
		,precisionLessThanErrMsg: "Value cannot be less than the existing value"
		,onlyRelativeAndAbsoluteErrMsg: "Only 'Relative' and 'Absolute' will be applicable for Performance Fee method 'Contingent Redemption Equalization'"
		,requiredFieldErrMsg: "This field is required."
		,requiredGreaterThanZero: "This field must be greater than zero."
		,negativeValueNotAllowed: "Negative value is not allowed."
		,alreadyExists:  "already exists."
		,hurldeRequired: "Hurdle set up is mandatory."
		,performanceFee: "Performance Fee"
		,applicable: "Applicable"
	}	
	,'frCA': {
		feeMethod: "Méthode de frais"
		,calcBasis: "Base de calcul"
		,lossCarryForward: "Option de report de pertes"
		,divAddBack: "Option de traitement des dividendes"
		,lotRedMethod: "Méthode de réduction de lots par défaut"
		,perfFeeCalcPrecision: "Précision du calcul"
		,perfFeePrecision: "Précision des frais liés au rendement"
		,gavRate: "VBA initiale"
		,classHWMRate: "CDP initiale par part"
		,classHWMResetDate: "Date CDP intiale"
		,hurdle: "Rendement minimum"
		,initValues: "Valeurs initiales"
		,benchmarkType: "Type d'indice"
		,fixRate: "Taux fixe"
		,benchmarkIndex: "Indice de référence"
		,benchmarkAdjRate: "Taux d'ajustement de l'indice "
		,daysBasis: "Base journalière"
		,weighting: "Pondération"
		,ReturntoSummary: "Retour au sommaire"
		,weightingErrMsg: "La somme des pondérations doit atteindre 100 %"
		,hurldeConfigErrMsg: "Aucune configuration pour le rendement minimum entré."
		,precisionLessThanErrMsg: "La valeur ne peut être inférieure à la valeur existante"
		,onlyRelativeAndAbsoluteErrMsg: "Pour la méthode de frais par 'égalisation des rachats contingentés' seules des valeurs 'relatives' et 'absolues' seront applicables"
		,requiredFieldErrMsg: "Ce champ est requis"
		,requiredGreaterThanZero: "Ce champ doit être supérieur à zéro"
		,negativeValueNotAllowed: "Valeur négative non acceptée"
		,alreadyExists:  "Déjà existant"
		,hurldeRequired: "Création du taux de rendement minimum obligatoire"
		,performanceFee: "Frais liés au rendement"
		,applicable: "Applicable"
	}	
}

