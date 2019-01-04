/*********************************************************************************************
 * @file    RegAgreement.Translation.js
 * @author  Hatthaseriphong, Nopphawan
 * @desc    Translation JS file of the Regulatory Agreement Maintenance
 *********************************************************************************************/
/*
 * Procedure: RegAgreement.Translation.js
 *
 * Purpose  : Translation for Regulatory Agreement Maintenance screen
 *
 * Notes    : - Regulatory Agreement Maintenance
 *            - Open screen from 
 *              Menu -> Broker Level Maintenance -> Regulatory Agreement Maintenance
 *
 * History  :
 *
 *    08 Feb 2017 N. Hatthaseriphong P0262306 CHG0048101 T85011 Regulatory Agreement Maintenance
 *        - Created
 *
 *    27 Feb 2017 Gomoot T. P0262306 CHG0048101 T85392 DFT0074488
 *        - Add logic to validate Effective date and stopdate
 *       
 *    19 Feb 2018 Matira T. P0268206-128 DFT0078815 DFT0080777
 *    		- Add Classification
 */

DesktopWeb.ScreenTranslation = {	
	'enUS': {
		RegAgmtMt: "Regulatory Agreement Maintenance"
		,Regulation: "Regulation"
		,SearchFor: "Search For"
		,SearchId: "Search ID"
		,All: "All"
		,PayType: "Pay Type"
		,PartyType: "Party Type"
		,PartyCode: "Party Code"
		,StartDate: "Start Date"
		,StopDate: "Stop Date"
		,ReceiptDate: "Receipt Date"
		,Status: "Status"
		,Code: "Code"
		,Name: "Name"
		,Responsibility: "Responsibility"
		,AccountDesignation: "Account Designation"
		,AccountableParty: "Accountable Party"
		,SetByDefault: "Set by Default"
		,EmptyText_All: "SEARCH BY ALL CODE"
		,EmptyText_Broker: "SEARCH BY BROKER NAME/CODE"
		,EmptyText_Intermediary: "SEARCH BY INTERMEDIARY NAME/CODE"
		,Search: "Search"
        ,Error_StopDateNotPriorEffDate: "Stop Date cannot be prior to Effective Date"
        ,Classification: "Classification"
	}
	
	,'frCA': {
		RegAgmtMt: "Suivi entente réglementaire"
		,Regulation: "Réglementation"
		,SearchFor: "Recherche"
		,SearchId: "Recherche d'identifiants"
		,All: "Tout"
		,PayType: "Type de paye"
		,PartyType: "Type de partie"
		,PartyCode: "Code de la partie"
		,StartDate: "Date de début"
		,StopDate: "Date d'arrêt"
		,ReceiptDate: "Date du reçu"
		,Status: "Statut"
		,Code: "Code"
		,Name: "Nom"
		,Responsibility: "Responsabilité"
		,AccountDesignation: "Désignation du compte"
		,AccountableParty: "Partie responsable"
		,SetByDefault: "Réglage par défaut"
		,EmptyText_All: "RECHERCHE PAR TOUS LES CODES"
		,EmptyText_Broker: "RECHERCHE PAR COURTIER/CODE"
		,EmptyText_Intermediary: "RECHERCHE PAR INTERMÉDIAIRE/CODE"
		,Search: "Recherche"
        ,Error_StopDateNotPriorEffDate: "La date de fin ne peut pas être antérieure à la date d'effet"
        ,Classification: "Classification"
	}
}