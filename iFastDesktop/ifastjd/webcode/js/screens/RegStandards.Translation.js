/*********************************************************************************************
 * @file	RegStandards.Translation.js
 * @author	
 * @desc	Translation JS file for Regulatory Document screen.
 *********************************************************************************************/
 /*
 * History : 
 *
 *    05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *    3 Feb 2017  Winnie Cheng P0259672  T84745
 *			  - Add ability to display French for CRS Report and Jurisdisction new labels
 *
 * 	  23 March 2017  Winnie Cheng P0259672  T85110
 *			  - remove one plural of heading
 * 
 * 	  29 March 2017  Winnie Cheng P0259672  T85194
 *			  - recheckIn with PDSOE setting encode - UTF-8
 */
 
DesktopWeb.ScreenTranslation = {
	
	'enUS': {		
		regulationRule: 'Regulation Rule'
		,ValidTaxTypes: 'Valid Tax Types'	
		,ValidAcctType: 'Valid Acct Types'
		,country: 'Country'
		,regulatoryStandard: 'Regulatory Standard'
		,regulatoryCode: 'Regulatory Code'
		,description: 'Description'
		,province: 'Province'
		,investorType: 'Investor Type'
		,fundCategory : 'Fund Category'
		,lowerBound : 'Lower Bound'
		,upperBound : 'Upper Bound'
		,investOnBehalfOfTP: 'Invest On Behalf Of 3rd Party'		
		,taxTypes: 'Tax Type(s)'
		,Chooseoptionsto: 'Choose Options to'
		,Include:'Include'
		,Exclude:'Exclude'
		,acctType : 'Account Type(s)'
		,actionCode : 'Action Code'
		,documentCode: 'Document Code'
		,docCode: 'DocCode'
		,descriptionComboEmptyText: 'Select document ...'
		,DeleteConfirmMsg: '<b>Regulatory Standard might be in use by existing accounts. Do you want to proceed with the deletion?</b>'
		,ModelCode: 'Model Code'
		,acctDesignation: 'Account Designation(s)'
		,FATCARegulation: 'Regulation'
		,reportToCountry: 'Report To Country'
		,reportableJurisdisctions: 'Reportable Jurisdictions'
		,reportableJurisdisction: 'Reportable Jurisdiction'
		,jurisdictions: 'Jurisdictions'
		,jurisdictionGridHeading: 'Jurisdiction'
		,taxJurisdictions: 'Tax Jurisdictions'
		,startDate: 'Start Date'
		,ERR_STOPDATE_CANNOT_LESS_THAN_DEFF: "Effective date cannot be later than stopdate."
		,ERR_DUPLICATED_CRSJURISDICTION: "Reportable Jurisdiction already exists."
		,OVERLAPPINGDATESERROR: 'The Reportable Jurisdiction for this compliance rule for this date range already exists.'
		,SINGLE: 'SINGLE'
		,MULTIPLE: 'MULTIPLE'
	},	
	'frCA': {
		regulationRule: "Norme réglementaire"
		,ValidTaxTypes: "Catégorie fiscale valable"	
		,ValidAcctType: "Type de compte valable"
		,country: "Pays"
		,regulatoryStandard: "Norme réglementaire"
		,regulatoryCode: "Code de réglementation"
		,description: "Description"
		,province: "Province"
		,investorType: "Type d'investisseur"
		,fundCategory : "Catégorie de fonds"
		,lowerBound : "Fourchette basse"
		,upperBound : "Fourchette haute"
		,investOnBehalfOfTP: "Investissement pour le compte d'un tiers"
		,taxTypes: "Type d'impôt"
		,Chooseoptionsto: "Choisir les options de"
		,Include: "Inclure"
		,Exclude: "Exclure"
		,acctType : "Types de comptes"
		,actionCode : "Code de documents"
		,documentCode: "Code de documents"
		,docCode: "Codedoc"
		,descriptionComboEmptyText: "Sélectionnez le document ..."
		,DeleteConfirmMsg: "<b>Norme réglementaire pourrait être utilisé par les comptes existants. Voulez-vous procéder à la suppression?</b>"
		,ModelCode: "Code de modèle"
		,acctDesignation: "Désignations comptable"		
		,FATCARegulation: "Réglementation"
		,reportToCountry:  "Pays du rapport"
		,reportableJurisdisctions: 'Territoires de référence'
		,reportableJurisdisction: 'Territoire de référence'
		,jurisdictions: 'Territoires'
		,jurisdictionGridHeading: 'Territoire'
		,taxJurisdictions: 'Territoires fiscaux'
		,startDate: 'Date de début'
		,ERR_STOPDATE_CANNOT_LESS_THAN_DEFF: "La date d'entrée en vigueur ne peut être postérieure à la date de."
		,ERR_DUPLICATED_CRSJURISDICTION: 'Une juridiction soumise à déclaration existe déjà.'
		,OVERLAPPINGDATESERROR: 'La juridiction soumise à déclaration relative à cette exigence de conformité existe déjà pour ces dates.'
		,SINGLE: 'Unique'
		,MULTIPLE: 'MULTIPLE'
	}
}