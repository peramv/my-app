/*********************************************************************************************
 * @file	FinInstIden.Translation.js
 * @author	Narin Suanlamyai
 * @desc	Translation JS file for Identification Maintenance screen.
 *********************************************************************************************/
/*
 * Procedure: FinInstIden.Translation.js
 *
 * Purpose  : Translation filed for Financial Institution Identification screen
 *             
 * Notes    : Setup Financial Institution Identification
 *            - Open screen from 
 *               Menu -> System Maintenance -> Financial Institution Identification
 *
 * History  :  
 *		18 Jul 2013 N. Suanlamyai P0193400 T53802
 *					- Created
 *
 *    05 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030135 T54881 
 *             - Add ability to display French 
 *
 *    13 Mar 2014 G. Thawornwachirakun P0223930 FN01 DFT0030359 T54882 
 *             - Revert missing code from T54881
 */

DesktopWeb.ScreenTranslation = {
	
	'enUS': {
		SearchFor: "Search For"
		,SearchID: "Search ID"
		,SearchByFund: "SEARCH BY FUND NAME/CODE/ISN/WKN"
		,SearchByFundGroup: "SEARCH BY FUND GROUP NAME/CODE"
		,SearchByLegalEntity: "SEARCH BY SPONSORING ENTITY NAME/CODE"
		,SearchByBroker: "SEARCH BY BROKER NAME/CODE"
		,SearchByIntermediary: "SEARCH BY INTERMEDIARY NAME/CODE"
		,EmptyText_Fund: "FUND NAME/CODE/ISN/WKN"
		,EmptyText_FundGroup: "FUND GROUP NAME/CODE"
		,EmptyText_LegalEntity: "SPONSORING ENTITY NAME/CODE"
		,EmptyText_Broker: "BROKER NAME/CODE"
		,EmptyText_Intermediary: "INTERMEDIARY NAME/CODE"
		,Label_Fund: "Fund"
		,Label_FundGroup: "Fund Group"
		,Label_LegalEntity: "Sponsoring Entity"
		,Label_Broker: "Broker"
		,Label_Intermediary: "Intermediary"
		,SearchResult: "Search Result"
		,IDType: "ID Type"
		,IDValue: "ID Value"
		,CountryOfIssue: "Country Of Issue"
		,Identification: "Identification"
		,IdentificationDetails: "Identification Details"
		,ERROR_GIIN_Invalid_Format: "GIIN format is incorrect."
		,ERROR_StopDateNotPriorEffectiveDate: "Stop Date cannot be prior to Effective Date."
		,ERROR_RecordNotAllowToDelete: "This record is not allowed to be deleted."
	}	
	
	,'frCA': {
		SearchFor: "Recherche"
		,SearchID: "Recherche de code"
		,SearchByFund: "RECHERCHE PAR NOM/CODE/ISN/WKN DU "
		,SearchByFundGroup: "RECHERCHE PAR GROUPE/NOM DE FONDS"
		,SearchByLegalEntity: "RECHERCHE PAR ENTITÉ PROMOTRICE/CODE"
		,SearchByBroker: "RECHERCHE PAR COURTIER/CODE"
		,SearchByIntermediary: "RECHERCHE PAR INTERMÉDIAIRE/CODE"
		,EmptyText_Fund: "NOM/CODE/ISN/WKN DU FONDS"
		,EmptyText_FundGroup: "GROUPE/CODE DU FONDS"
		,EmptyText_LegalEntity: "ENTITÉ PROMOTRICE/ CODE"
		,EmptyText_Broker: "COURTIER/CODE"
		,EmptyText_Intermediary: "INTERMÉDIAIRE/CODE"
		,Label_Fund: "Fonds"
		,Label_FundGroup: "Groupe de fonds"
		,Label_LegalEntity: "Entité promotrice"
		,Label_Broker: "Courtier"
		,Label_Intermediary: "Intermédiaire"
		,SearchResult: "Résultats de la recherche"
		,IDType: "Type de code"
		,IDValue: "Valeur"
		,CountryOfIssue: "Pays d'émission"
		,Identification: "Identification"
		,IdentificationDetails: "Détails de l'identification"
		,ERROR_GIIN_Invalid_Format: "Le format NIIM n'est pas valable."
		,ERROR_StopDateNotPriorEffectiveDate: "La date de fin ne peut pas être antérieure à la date d'effet"
		,ERROR_RecordNotAllowToDelete: "TCette donnée ne peut pas être effacée"
	}	
}