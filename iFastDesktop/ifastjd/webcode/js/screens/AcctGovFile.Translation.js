/*********************************************************************************************
 * @file	AcctGovFile.Translation
 * @author 	Narin Suanlamyai
 * @desc	Translation JS file for Tax Payer Maintenance
 *********************************************************************************************/
/*
 * Procedure: AcctTaxAlloc.Translation.js
 *
 * Purpose  : Translation of Foreign Tax Review screens
 *             
 * Notes    : Open screens by COA -> Attributes Box -> Foreign Tax Review
 *						or Menu -> Account Level Maintenance -> Foreign Tax Review
 *
 * History  : 
 *      28 Sep 2012 H.Sartsangchan Created. 
 *                  IN3102195 PETP0179630 FN01 Fatca
 *                  - Add France Translation with English Translation wait to completed
 *                                    
 *		20 Jan 2014 Narin Suanlamyai P0223930 FN01 - FATCA 1C
 *					- Add required translations for new screen labels
 *
 *		26 Feb 2014 G. Thawornwachirakun P0223930 DFT0029664 T54848
 *					- Relabel from Indicia Status to Due Diligence Status
 *
 *    05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *    17 Jul 2017 Matira T. P0264940 P0264940-50 FATCA - CRS Coc
 *          - Change Indicia to Indicia/Change 
 */
 
DesktopWeb.ScreenTranslation = {
	'enUS': {	
		 Status: "Due Diligence Status"
		,title: "Account Level Foreign Tax Review"
		,StartDate: "Start Date"
		,EndDate: "End Date"
		,EntityAccount: "Type Of Acct"
		,FilingType: "Filing Type"
		,CompliantCode: "Compliant Code"
		,EffectiveDate: "As of Date"
		,ReviewDate: "Run Date"
		,IndiciaSearch: "Indicia/Change Search"		
		,SearchResult: "Search Results"
		,Country: "Country"
		,CompliantCodeDescription: "Compliant Code Description"
		,Remarks: "Remarks"
		,IndiciaSearchResult: "Indicia/Change Search Results"
		,EntityType: "EntityType"
		,Name: "Name"
		,FieldName: "Indicia/Change Element"
		,FieldValue: "Field Value"
		,Historical: "Historical"
		,AccountStatus: "Account Status"
		,AccountType: "Account Type"
		,TaxType: "Tax Type"
		,Error_PendingReviewStatusAlreadyExists: "Duplicate Check Failed: Only one Pending Review request is allowed for an account/comply code."
		,Error_DocumentAlreadyReviewed: "Validate Check Failed: Document has been reviewed. Document status is not allowed to be Pending Review."
		,Error_StartDateNotPriorEndDate: "Start Date cannot prior to End Date"
		,Warning_ReviewAllocationPercentage: "Please review the allocation % on the Account Ownership Allocation screen and make corresponding adjustment."
		,AcctOpenDate: "Account Open Date"
		,AcctBalance: "Account Balance"
		,Currency: "Currency"
		,Regulation: "Tax Regulation"
		,AccountOwner: "Account Owner"
		,ReportingFFI: "ReportingFFI"
		,CountryOfRFFI: "Country of RFFI"
		,HoldingBalance: "Holding Balance"
		,AggregateBalance: "Aggregate Balance"
		,HoldingDetails: "Holding Details"
	}
	
	,'frCA': {
		Status: "Statut de diligence raisonnable"
		,title: "Niveau de compte pour revue impôt étranger"
		,StartDate: "Date de début"
		,EndDate: "Date de fin"
		,EntityAccount: "Type Of Acct" /*no use*/
		,FilingType: "Filing Type"  /*no use*/
		,CompliantCode: "Compliant Code"  /*no use*/
		,EffectiveDate: "En date du"
		,ReviewDate: "Date de traitement"
		,IndiciaSearch: "Recherche indices/changement"
		,SearchResult: "Résultats de la recherche"
		,Country: "Pays"
		,CompliantCodeDescription: "Compliant Code Description" /*no use*/
		,Remarks: "Remarks"  /*no use*/
		,IndiciaSearchResult: "Résultats recherche indices/changement"
		,EntityType: "Type d'entités"
		,Name: "Nom"
		,FieldName: "Élément indices/changement"
		,FieldValue: "Valeur du champ" 
		,Historical: "Historical" /*no use*/
		,AccountStatus: "Statut du compte"
		,AccountType: "Type de compte"
		,TaxType: "Type d'impôt"
		,Error_PendingReviewStatusAlreadyExists: "Duplicate Check Failed: Only one Pending Review request is allowed for an account/comply code."
		,Error_DocumentAlreadyReviewed: "Validate Check Failed: Document has been reviewed. Document status is not allowed to be Pending Review."
		,Error_StartDateNotPriorEndDate: "Start Date cannot prior to End Date"
		,Warning_ReviewAllocationPercentage: "Please review the allocation % on the Account Ownership Allocation screen and make corresponding adjustment."
		,AcctOpenDate: "Date d'ouverture du compte"
		,AcctBalance: "Account Balance" /*no use*/
		,Currency: "Currency" /*no use*/
		,Regulation: "Réglementation fiscale"
		,AccountOwner: "Account Owner"  /*no use*/
		,ReportingFFI: "Rapport IFE"
		,CountryOfRFFI: "Pays de l'IFE "
		,HoldingBalance: "Solde position"
		,AggregateBalance: "Solde consolidé"
		,HoldingDetails: "Holding Details"  /*no use*/
	}
}