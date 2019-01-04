/*********************************************************************************************
 * @file	FinanInst.Translation.js
 * @author	Sukjaitham, Supareuk
 * @desc	Translation JS file for Financial Institution Regulatory screen.
 *********************************************************************************************/
/*
 * Procedure: FinanInst.Translation.js
 *
 * Purpose  : Translation for Financial Institution Regulatory screen
 *             
 * Notes    : - Setup Financial Institution Regulatory
 *            - Open screen from 
 *               Menu -> System Maintenance -> Financial Institution Regulatory
 *
 * History  :  
 *		18 Jul 2013 S. Sukjaitham, G. Thawornwachirakun P0193400 T53802
 *					- Created.
 *
 *		23 Aug 2013 G. Thawornwachirakun P0193400 DFT0014730 T54066
 *                  - Add new identification warning message 
 *
 *    
 *    7 Mar 2014 Winnie Cheng P0223057 T77835 DFT0030208
 *                  - Adding more title for segerated screens
 *
 *    10 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *    13 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030359 T54882 
 *             - Revert missing code from T54881
 *
 *    19 Jan 2015 A. Mongkonrat P0205605 I0 T80201
 *             - FATCA Phase II.
 *
 *    21 Dec 2015 Watchara Th. P0241558 T81890 FATCA Reporting Enhancement
 *					- Add new tabs (Address and Contact) for
 *					  Fund/Fund Group level and Sponsoring Entity level.
 *
 *    06 Jan 2016 Aurkarn M. P0241558 T81995 DFT0058373 DFT0058365 FATCA Reporting Enhancement 
 *					- Redesign Address/Contact tabs
 *
 *    06 Jul 2016 Matira T. P0255392 T83155 2016 FATCA Reporting Enhancements
 *					- Add french for field FISponsor and alert msg.
 *
 *    3 Feb 2017  Winnie Cheng P0259672  T84745
 *			  - Enhance the screen for CRS Report regulation rule and FATCA change accordingly
 * 
 * 	  29 March 2017  Winnie Cheng P0259672  T85194
 *			  - recheckIn with PDSOE setting encode - UTF-8
 *
 *	  7 Nov 2018  Umamahesh  P0277786-178 FATCA 19.2 
 *			  - Adding label for Filer Category for FATCA/CRS.
 */

DesktopWeb.ScreenTranslation = {
	
	'enUS': {
		FIscreen: "Financial Institution Regulatory Details"
		,Regulation: "Regulation"
		,SearchFor: "Search For"
		,Identifier: "Identifier"
		,SearchID: "Search ID"
		,SearchByFund: "SEARCH BY FUND NAME/CODE/ISN/WKN"
		,SearchByFundGroup: "SEARCH BY FUND GROUP NAME/CODE"
		,SearchByLegalEntity: "SEARCH BY SPONSORING EnTiTy NAME/CODE"
		,SearchByBroker: "SEARCH BY BROKER NAME/CODE"
		,SearchByIntermediary: "SEARCH BY INTERMEDIARY NAME/CODE"
		,EmptyText_Fund: "FUND NAME/CODE/ISN/WKN"
		,EmptyText_FundGroup: "FUND GROUP NAME/CODE"
		,EmptyText_LegalEntity: "SPONSORING ENTITY NAME/CODE"
		,EmptyText_Broker: "BROKER NAME/CODE"
		,EmptyText_Intermediary: "INTERMEDIARY NAME/CODE"
		,Fund: "Fund"
		,FundGroup: "Fund Group"
		,LegalEntity: "Sponsoring Entity"
		,Broker: "Broker"
		,Intermediary: "Intermediary"
		,Classification: "Classification"
		,ReportingFFI: "Reporting FFI"
		,ReportingUnit: "Reporting Unit"
		,Description: "Description"
		,Model: "Model"
		,ApplyThreshold    : "Apply Lower Threshold"
		,ApplyThresholdDate: "Pre-Exist Acct As of"
		,Identification: "Identification"
		,Responsibility: "Broker / Intermediary Responsibility"
		,ResponsibilityColumn: "Responsibility"
		,ClientHeld: "Client Held Acct"
		,NomineeHeld: "Nominee Held Acct"
		,IntermediaryHeld: "Intermediary Held Acct"
		,DocumentTracking: "Document Tracking"
		,WidthHolding: "Withholding"
		,Reporting: "Reporting"
		,FIDetails: "Financial Institution Regulatory Details"
		,FIFundScreen: "Fund Regulatory Details"
		,FIBrokerScreen: "Broker Regulatory Details"
		,FIIntermediaryScreen: "Intermediary Regulatory Details"
		,IDType: "ID Type"
		,IDValue: "ID Value"
		,CountryOfIssue: "Country Of Issue"
		,Label_Code: "Code"
		,IdentificationDetails: "Identification Details"
		,Error_FFILevelRequire:"Search For must be entered"
		,Error_RegulationeRequire : "Regulation must be entered"
		,Error_StopDateNotPriorEffDate: "Stop Date cannot be prior to Effective Date"
		,ERROR_GIIN_Invalid_Format: "GIIN format is incorrect."
		,ERROR_Identification: "Identification Error"
		,WARNING_Identification: "Identification Warning"
		,Country: "Country"
		,AggregationFFI: "Aggregation FFI"
		,Address: "Address"
		,Contact: "Contact"		
		,Address1: "Address - Line 1"
		,Address2: "Address - Line 2"
		,Address3: "Address - Line 3"
		,City: "City"
		,Province: "Province/State"
		,PostalCode: "Zip/postal code"	
		,Country: "Country"
		,ContactName: "Contact Name"
		,ContactPhoneAreaCode: "Contact Phone Area Code"
		,ContactPhoneNumber: "Contact Phone Number"
		,ContactPhoneExtNumber: "Contact Phone Extension Number"
		,ContactEmail: "Contact Email Address"		
		,FISponsor: "FI Sponsor"
		,PhoneWrnMsg: "Contact Phone Number is invalid"
		,ERR_DUPLICATED_RECORD: 'Duplicate records with overlapping dates.'
		,ERR_DUPLICATED_IDEN: 'Duplicated Identification.'
		,filerCategory: 'Filer Category'
	}	
	
	,'frCA': {
		FIscreen: "Détails réglementaires sur l'institution financière"
		,FIFundScreen: "Détails sur le fonds de réglementation"
		,FIBrokerScreen: "Détails du courtier réglementation"
		,FIIntermediaryScreen: "Détails réglementaires intermédiaires"
		,Regulation: "Réglementation"
		,SearchFor: "Recherche"
		,Identifier: "Code"
		,SearchID: "Recherche de code"
		,SearchByFund: "RECHERCHE PAR NOM/CODE/ISN/WKN DU FONDS"
		,SearchByFundGroup: "RECHERCHE PAR GROUPE/NOM DE FONDS"
		,SearchByLegalEntity: "RECHERCHE PAR ENTITÉ PROMOTRICE/CODE"
		,SearchByBroker: "RECHERCHE PAR COURTIER/CODE"
		,SearchByIntermediary: "RECHERCHE PAR INTERMÉDIAIRE/CODE"
		,EmptyText_Fund: "NOM/CODE/ISN/WKN DU FONDS"
		,EmptyText_FundGroup: "GROUPE/CODE DU FONDS"
		,EmptyText_LegalEntity: "ENTITÉ PROMOTRICE/ CODE"
		,EmptyText_Broker: "COURTIER/CODE"
		,EmptyText_Intermediary: "INTERMÉDIAIRE/CODE"
		,Fund: "Fonds"
		,FundGroup: "Groupe de fonds"
		,LegalEntity: "Entité promotrice"
		,Broker: "Courtier"
		,Intermediary: "Intermédiaire"
		,Classification: "Classification"
		,ReportingFFI: "Rapport IFE"
		,ReportingUnit: "Reporting Unit"
		,Description: "Description"
		,Model: "Modèle"
		,ApplyThreshold    : "Appliquer le seuil inférieur"
		,ApplyThresholdDate: "Compte préexistant, au"
		,Identification: "Identification"
		,Responsibility: "Courtier/responsabilité intermédiaire"
		,ResponsibilityColumn: "Responsabilité"
		,ClientHeld: "Compte détenu par le client"
		,NomineeHeld: "Compte détenu par le représentant"
		,IntermediaryHeld: "Compte détenu par l'intermédiaire"
		,DocumentTracking: "Suivi des documents"
		,WidthHolding: "Retenue"
		,Reporting: "Rapport"
		,FIDetails: "Détails réglementaires sur l'institution financière"
		,FundDetails: "Fund Regulatory Details"
		,IntDetails: "Intermediary Institution Regulatory Details"
		,BrokerDetails: "Broker Regulatory Details"
		,IDType: "Type de code"
		,IDValue: "Valeur"
		,CountryOfIssue: "Pays d'émission"
		,Label_Code: "Code"
		,IdentificationDetails: "Détails de l'identification"
		,Error_FFILevelRequire:"Rechercher doit être entré."
		,Error_RegulationeRequire : "Règlement doit être entré."
		,Error_StopDateNotPriorEffDate: "La date de fin ne peut pas être antérieure à la date d'effet"
		,ERROR_GIIN_Invalid_Format: "Le format NIIM n'est pas valable."
		,ERROR_Identification: "Identification d'erreur"
		,WARNING_Identification: "Identification avertissement"
		,Country: "Pays"
		,AggregationFFI: "Regroupement IFE"
		,Address: "Address"
		,Contact: "Contact"
		,Address1: "Address - Line 1"
		,Address2: "Address - Line 2"
		,Address3: "Address - Line 3"
		,City: "City"
		,Province: "Province/State"
		,PostalCode: "Zip/postal code"	
		,Country: "Country"
		,ContactName: "Contact Name"
		,ContactPhoneAreaCode: "Contact Phone Area Code"
		,ContactPhoneNumber: "Contact Phone Number"
		,ContactPhoneExtNumber: "Contact Phone Extension Number"
		,ContactEmail: "Contact Email Address"		
		,FISponsor: "Commanditaire IF"
		,PhoneWrnMsg: "Le numéro de téléphone du contact n'est pas valide"
		,ERR_DUPLICATED_RECORD: 'Doublons ayant des dates qui se chevauchent.'
		,ERR_DUPLICATED_IDEN: 'Doublon Identification.'
		,filerCategory: 'Catégorie de classement'
	}
}