/*********************************************************************************************
 * @file	ClassSetup_BasicInfo.Translation.js
 * @author	
 * @desc	Translation JS file for ClassSetup Basic Information screen.
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
 *    13 Oct 2014 Supareuk Sukjaitham  P0230233 FNXX T56126
 *             - Added new warning message translation for Fund Class name auto-syncup project
 *             - Correct task number
 *
 *    24 July 2015 Winnie Cheng P0242521 FN01 T81053  R15.5
 *             - Added Prorated Transfer field to support MFS Proportional Transfers
 *             
 *     2 Feb 2015 dchatcha P0248860 CHG0043555 FN01 T82168 R16.3
 *          - Adding a new sub-category "GARS" for Manulife GARS and QROPS Reports
 *
 *    10 July 2016 Winnie Cheng P0255686 FN01 T83008 R16.5
 *          -  Adding a new "Allow Negative Balance" sub-category
 *
 *    22 July 2016 Matira T. P0256538 FN01 T83329 R16.5
 *          -  Adding 2 new sub-category: CustomPayOFnd and PortfolioPayOFnd
 *
 *  08 Nov 2016 Aurkarn M. P0256121 FN01 T84156 R17.2
 *          - Added translations of "Target Date Mutual Fund"
 *
 *  05 Sep 2017 Nopphawan H. P0269957 CHG0050809 T86217 R18.1
 *          - Added translations of "Multi Managed Funds"
 *
 *  29 Aug 2017 Matira T. P0271575 P0271575-11 R18.1
 *          - Added translations of "Price not required"
 *          
 *  07 Nov 2017 Sreejith A P0266789-1286 R18.2
 *          - Added translations of "MCH Assets" 
 */
 
DesktopWeb.ScreenTranslation = {
	
	'enUS': {
		FundCode: "Fund Code"
		,ClassCode: "Class Code"
		,EnglishDescription: "English Description"
		,FrenchDescription: "French Description"		
		,StatusDate: "Status Date"				
		,ESGCompanyCode: "ESG Company Code"
		,LoadType: "Load Type"
		,BareTrustee: "Bare Trustee"
		,RiskRating: "Risk Rating"
		,FundClassCurrHoliday: "Fund/Fund Class Curr Holiday"
		,BasedOn: "Based On"
		,Applicable: "Applicable"
		,PrivatePoolFund: "Private Pool Fund"
		,FundofFund: "Fund of Fund"
		,AllocatorFund: "Allocator Fund"
		,FlagshipFund: "Flagship Fund"
		,InstitutionalFund: "Institutional Fund"
		,PoolFunds: "Pool Funds"
		,CorporateClassFunds: "Corporate Class Funds"
		,InterestFund: "Interest Fund"
		,HighInterestInvestmentFund: "High Interest Investment Fund"
		,TaxSlipReporting: "Tax Slip Reporting"
		,OEICFunds: "OEIC Fund"
		,IdType: "Id Type"
		,IdValue: "Id Value"
		,GroupName: "Group Name"
		,Active: "Active"
		,FundIdentifier: "Fund Identifier"
		,FundIdentifiers: "Fund Identifiers"
		,ShareGroup: "Share Group"
		,ShareGroups: "Share Groups"
		,InventoryTracking: "Inventory Tracking"
		,FundSubCategories: "Fund Sub-Categories"		
		,ReturntoSummary: "Return to Summary"
		,TrackingType: "Tracking Type"
		,InventoryCategory: "Inventory Category"
		,TrailerPaymentFrequency: "Trailer Payment Frequency"
		,Section18Report:"Section 18 Report"
		,TSReportable:"TS Reportable"
		,FndClsNameSyncUpWarning: "Class description (in translation-info) will not be updated"
		,ProratedTransfer:"Prorated Transfers"
		,GARSFund:"GARS Fund"
		,AllowNegativeBalanceFund:"Allow Negative Balance"
		,CustomPayOFnd:"Custom Payout Fund"
		,PortfolioPayOFnd:"Portfolio Payout Fund"
		,TargetDateMutualFnd: "Target Date Mutual Fund"
		,MultiManagedFunds: "Multi Managed Funds"
		,PriceNotRequired: "Price Not Required"
		,MCHAssets: "MCH Assets"
	}
	
	,'frCA': {
		FundCode: "Code du fonds"
		,ClassCode: "Code de la catégorie"
		,EnglishDescription: "Termes anglais"
		,FrenchDescription: "Termes français"
		,StatusDate: "Date du statut"
		,ESGCompanyCode: "Code de la société GNE"
		,LoadType: "Type de téléchargement"
		,BareTrustee: "Nu fiduciaire"
		,RiskRating: "Évaluation du risque"
		,TrackingType: "Type de suivi"
		,FundClassCurrHoliday: "Jour férié de la monnaie de la classe du fonds/du fonds"
		,BasedOn: "Fondée sur"
		,Applicable: "Applicable"
		,PrivatePoolFund: "Fonds en commun privé"
		,FundofFund: "Fonds de fonds"
		,AllocatorFund: "Fonds de répartition"
		,FlagshipFund: "Fonds phare"
		,InstitutionalFund: "Fonds institutionnel"
		,PoolFunds: "Fonds en commun"
		,CorporateClassFunds: "Fonds de classe de société"
		,InterestFund: "Fonds d'intérêt"
		,HighInterestInvestmentFund: "Fonds de placement à intérêt élevé"
		,TaxSlipReporting: "Déclaration de feuillet d'imposition"
		,OEICFunds: "Fonds SICAV"
		,IdType: "Code de"
		,IdValue: "Code de valeur"
		,GroupName: "Nom du groupe"
		,Active: "Actif"
		,FundIdentifier: "Identificateur de fonds"
		,FundIdentifiers: "Identificateurs de fonds"
		,ShareGroup: "Groupe de parts"
		,ShareGroups: "Groupes de parts"
		,InventoryTracking: "Suivi d'inventaire"
		,FundSubCategories: "Sous-catégories de fonds"		
		,ReturntoSummary: "Retour au sommaire"	
		,InventoryCategory: "Catégorie d'inventaire"
		,TrailerPaymentFrequency: "Fréquence de paiement remorque"
		,Section18Report: "Rapport section 18"
		,TSReportable: "TS du rapport"
		,FndClsNameSyncUpWarning: "Description de la classe ne sera pas mis à jour"
		,ProratedTransfer:"Transfert au prorata"
		,GARSFund:"Fonds d'GARS"
		,AllowNegativeBalanceFund:"Autoriser un solde négatif"
		,CustomPayOFnd:"Custom Payout Fund"
		,PortfolioPayOFnd:"Portfolio Payout Fund"
		,TargetDateMutualFnd: "Date cible Fonds communs de placement"
		,MultiManagedFunds: "Fonds multi-géré"
		,PriceNotRequired: "Prix non demandé"
		,MCHAssets:"Actifs HMD"
	}
}