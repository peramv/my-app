/*********************************************************************************************
 * @file    TransferAccounts.Translation.js
 * @author  Mongkonrat, Aurkarn
 * @desc    Translation JS file Transfer of Accounts screen.
 *********************************************************************************************/
/*
 * Procedure: TransferAccounts.Translation.js
 *
 * Purpose  : Translation for Transfer of Accounts screen
 *
 * Notes    :
 *
 * History  :
 *
 *    22 Mar 2015 A. Mongkonrat P0246257 T82356 Dealer Service Bulk Transfer
 *        - Created
 *
 *    31 May 2016 N. Hatthaseriphong P0246257 T82943 Dealer Service Bulk Transfer
 *        - Add AUM Report.
 *        - Add effective date validation to check it must be the current date.
 *
 *    2 June 2016 N. Hatthaseriphong P0246257 T82943 
 *    DFT0063831 DFT0063832 DFT0064015 Dealer Service Bulk Transfer
 *        - Add AUM Report (French).
 *
 *    2 June 2016 N. Hatthaseriphong P0246257 T83014 
 *    DFT0064015 Dealer Service Bulk Transfer
 *        - Add AUM_Requested and Warn_Reversal (French).
 *        
 */

DesktopWeb.ScreenTranslation = {

    'enUS': {
        BulkTrferMaint: "Bulk Transfer Maintenance"
        ,BulkTrferDetl: "Bulk Transfer Details"
        ,BulkTrferID: "Bulk Transfer ID"
        ,AWDBatchID: "AWD Batch ID"
        ,BulkTransferActions: "Bulk Transfer Actions"
        ,Intermediary: "Intermediary"
        ,Add: "Add"
        ,Create: "Create"
        ,Modify: "Modify"
        ,Save: "Save"
        ,Print: "Print"
		,AUMReport: "AUM Report"
        ,Cancel: "Cancel"
        ,OK: "OK"
        ,View: "View"
        ,Approve: "Approve"
        ,Reject: "Reject"
        ,Reverse: "Reverse"
        ,From: "From"
        ,To: "To"
        ,Search: "Search"
        ,Status: "Status"
        ,StartDate: "Start Date"
        ,EndDate: "End Date"
        ,Broker: "Broker"
        ,Branch: "Branch"
        ,SalesRep: "Sales Rep"
        ,EffectiveDate: "Effective Date"
        ,BlockTrferType: "Block Transfer Type"
        ,AcctDesign: "Account Designation"
        ,Nominee: "Nominee"
        ,IntermediaryEntity: "Intermediary Entity"
        ,DateOfReversal: "Date of Reversal"
        ,CreatedBy: "Created by"
        ,ReversedBy: "Reversed by"
        ,BulkTrferApprovedBy: "Bulk Transfer Approved by"
        ,ReversalApprovedBy: "Reversal Approved by"
        ,RequestDateOfReversal: "Request Date of Reversal"
        ,ERR_REQUIRED_FIELD: "This field is required."
		,ERR_EFFECTIVEDATE_FIELD: "Bulk Transfer Effective Date must be current date."
        ,GRD_EffectiveDate: "Effective<br/>Date"
        ,GRD_DateOfReversal: "Date of<br/>Reversal"
        ,GRD_BlockTrferType: "Block<br/>Transfer Type"
        ,GRD_AcctDesign: "Account<br/>Designation"
        ,GRD_FromBroker: "From<br/>Broker"
        ,GRD_FromBranch: "From<br/>Branch"
        ,GRD_FromSlsRep: "From<br/>Sales Rep"
        ,GRD_ToBroker: "To<br/>Broker"
        ,GRD_ToBranch: "To<br/>Branch"
        ,GRD_ToSlsRep: "To<br/>Sales Rep"
        ,GRD_Action: "Action"
        ,GRD_DateTime: "Date Time"
        ,GRD_BulkTrferID: "Bulk Transfer ID"
        ,UserConfirm1: "Are you sure you want to "
        ,UserConfirm2: " this record?"
        ,AUM_Requested: "AUM report has been requested."
        ,Warn_Reversal: "WARNING: Compensation and other financial transactions WILL NOT BE REVERSED. \
                         Reversal reinstates only the Dealer/Sales Rep code"
    }

    ,'frCA': {
        BulkTrferMaint: "Entretien du transfert en bloc"
        ,BulkTrferDetl: "Détails de transfert en bloc"
        ,BulkTrferID: "Coordonnées du transfert en bloc"
        ,AWDBatchID: "Coordonnées lot AWD"
        ,BulkTransferActions: "Action du transfert en bloc"
        ,Intermediary: "Intermédiaire"
        ,Add: "Ajouter"
        ,Create: "Créer"
        ,Modify: "Modifier"
        ,Save: "Enregistrer"
        ,Print: "Imprimer"
		,AUMReport: "Rapport ASG"
        ,Cancel: "Annulation"
        ,OK: "OK"
        ,View: "Visualiser"
        ,Approve: "Approuver"
        ,Reject: "Rejeter"
        ,Reverse: "Contrepasser"
        ,From: "De"
        ,To: "Vers"
        ,Search: "Recherche"
        ,Status: "Statut"
        ,StartDate: "Date de début"
        ,EndDate: "Date de fin"
        ,Broker: "Courtier"
        ,Branch: "Agence"
        ,SalesRep: "Représentant"
        ,EffectiveDate: "Date d'effet"
        ,BlockTrferType: "Type de transfert en bloc"
        ,AcctDesign: "Désignation du compte"
        ,Nominee: "Représentant"
        ,IntermediaryEntity: "Entité intermédiaire"
        ,DateOfReversal: "Date de contrepassation"
        ,CreatedBy: "Créé par"
        ,ReversedBy: "Contrepassé par"
        ,BulkTrferApprovedBy: "Transfert en bloc approuvé par"
        ,ReversalApprovedBy: "Contrepassation approuvée par"
        ,RequestDateOfReversal: "Date de demande de contrepassation "
        ,ERR_REQUIRED_FIELD: "Ce champ est requis"
		,ERR_EFFECTIVEDATE_FIELD: "La date d'effet du transfert en bloc doit être datée d'aujourd'hui."
        ,GRD_EffectiveDate: "Date d'effet"
        ,GRD_DateOfReversal: "Date de<br/>contrepassation"
        ,GRD_BlockTrferType: "Type de transfert<br/>en bloc"
        ,GRD_AcctDesign: "Désignation<br/>du compte"
        ,GRD_FromBroker: "Du<br/>courtier"
        ,GRD_FromBranch: "De l'agence"
        ,GRD_FromSlsRep: "Du<br/>représentant"
        ,GRD_ToBroker: "Au<br/>courtier"
        ,GRD_ToBranch: "À l'agence"
        ,GRD_ToSlsRep: "Au<br/>représentant"
        ,GRD_Action: "Action"
        ,GRD_DateTime: "Date et heure"
        ,GRD_BulkTrferID: "Coordonnées du<br/>transfert en bloc"
        ,UserConfirm1: "Êtes-vous sûr de vouloir "
        ,UserConfirm2: " cet enregistrement?"
        ,AUM_Requested: "Un rapport d'ASG a été demandé."
        ,Warn_Reversal: "ATTENTION: la rétribution et d'autres transactions financières NE SERONT PAS CONTREPASSÉES. \
                         La contre-passation ne réinitialise que le code du courtier/représentant."
    }
}