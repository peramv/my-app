/*********************************************************************************************
 * @file	ClassSetup_Search.Translation.js
 * @author	
 * @desc	Translation JS file for ClassSetup Search screen.
 *********************************************************************************************/
 /*
 * History : 
 *
 * 05-Mar-2014 Gomoot T. P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *  24 March 2015 P0181067 T80539 DFT0045635 FundFeeConfig setup for Advisor Fee 
 *          - Move Management Fee, Management Fee Rebate and Advisor Fee from Fee Configuration to Fee Model Configuration.
 *          
 *  14-Nov-2017 Sreejith A P0266789-1615
 *  		- Added translation for APIR
 *  
 *	 8 Jan 2018	Sreejith A P0274727 P0274727-1
 *			- Added "settle day controls"
 *
 *   1 Feb 2018	Sreejith.A P0274726 P0274726-49
 *			- Added translations for remarks popup  
 *
 *	22 Mar 2018 Sreejith.A P0274727 P0274727-88
 *			- T+0 Project P0274727 changes revert from 18.3
 *
 *	12 Jun 2018 Sreejith.A P0277704 P0277704-17
 *			- T+0 Project put back reverted changes for trade control and settle date control
 */  

DesktopWeb.ScreenTranslation = {
	
	'enUS': {
		LookupClasses: "Lookup Classes"		
		,ISIN: "ISIN"
		,CUSIP: "CUSIP"
		,WKNFundId: "WKN Fund Id"
		,ExternalFundId: "External Fund Id"
		,FundLoadGroup: "Fund Load Group"
		,AddClass: "Add Class"
		,ViewClassDetails: "View Class Details"
		,LimitationOverride: "Limitation Override"
		,BasicInfo: "Basic Information"
		,TradeConfig: "Trade Configuration"
		,DistConfig: "Distribution Configuration"
		,PriceInfo: "Price Information"
		,FeeConfig: "Fee Configuration"
		,FeeModelConfig: "Fee Model Configuration"
		,TradeDayCtrls: "Trade Day Controls"
		,SettleDayCtrls: "Settle Day Controls"
		,GIAAttributes: "GI Attributes"
		,IntConfig: "Interest Configuration"		
		,PerfFeeConfig: "Performance Fee"
		,EventFreq: "Event Schedule"
		,emptyTextSearch: "SEARCH BY FUND NAME/CODE/ISN/WKN/APIR"
		,APIR: "APIR"
		,Remarks: "Remarks"
		,Reason: "Reason"
		,RemarkType: "Remark Type"
		,EffectiveDate: "Effective Date"
		,ERR_DUPLICATED_REMARKTYPE : "Another remark already exists for that Remark Type. Only one remark can exist for each Remark Type"
		,ERR_REASON_REMARK_MAND : "One of Reason or Remarks must be filled in. Both can not be empty"
	}
	
	,'frCA': {
		LookupClasses: "Classes de recherche"
		,ISIN: "ISIN"
		,CUSIP: "CUSIP"
		,WKNFundId: "Code de fonds WKN"
		,ExternalFundId: "Code de fonds externe"
		,FundLoadGroup: "Groupe de frais du fonds"
		,AddClass: "Ajouter une classe"
		,ViewClassDetails: "Voir les détails de la classe"
		,LimitationOverride: "Modification de limitation"
		,BasicInfo: "Information de base"
		,TradeConfig: "Configuration de la transaction"
		,DistConfig: "Configuration de la distribution"
		,PriceInfo: "Information sur le prix"
		,FeeConfig: "Configuration des frais"
		,FeeModelConfig: "Configuration des Modèle de frais"
		,TradeDayCtrls: "Contrôles de jour de transaction"
		,SettleDayCtrls: "Caractéristiques des jours de règlement"
		,GIAAttributes: "Attributs d'intérêt garanti"
		,PerfFeeConfig: "Frais liés au rendement"
		,EventFreq: "Échéancier d'évènements"
		,emptyTextSearch : "RECHERCHE PAR NOM/CODE/ISN/WKN DU FONDS/RIAP"
		,APIR: "RIAP"
		,Remarks: "Remarques"
		,Reason: "Raison"
		,RemarkType: "Types de remarques"
		,EffectiveDate: "Date effective"
		,ERR_DUPLICATED_REMARKTYPE : "Une autre remarque existe pour ce type de remarque. Il ne peut exister qu'une remarque par type de remarque"
		,ERR_REASON_REMARK_MAND : "Un motif ou des remarques doivent être renseignés. Aucun champ ne peut être laissé vide"
	}
}
