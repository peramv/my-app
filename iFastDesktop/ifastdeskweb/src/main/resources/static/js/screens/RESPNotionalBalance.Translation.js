/*********************************************************************************************
 * @file    RESPNotionalBalance.Translation.js
 * @author  Narin Suanlamyai
 * @desc    Translation JS file for RESP Notional Balance screen.
 *********************************************************************************************/
/*
 * History : 
 *
 *  16 Jun 2015 Narin Suanlamyai P0241773 T81011
 *      - Initial (Rewriting RESP Notional Info screen)
 *
 *  13 Jul 2015 Narin Suanlamyai P0241773 T81239
 *      - Add Adjustment pop-up
 *
 *  10 Sep 2015 Gulputt Dechvichankit P0241773 T81342
 *      - Add French translation.
 *
 *  17 Sep 2015 Narin Suanlamyai P0241773 T81293
 *      - Add error message if bucket is going to be negative
 *
 *  11 Dec 2015 Narin Suanlamyai P0241773 DFT0056498 T81878
 *      - Fixed error message when adjusted balance is going to be negative
 *
 *  05 Jan 2016 Nopphawan Hatthaseriphong P0250179 DFT0058218 T82197
 *      - Add Contribution (both of English and French)
 *
 *  15 Aug 2017 Matira T. P0256094 DFT0076357 T86053
 *      - Change Translation Returned to Repayment
 */
DesktopWeb.ScreenTranslation = {
    "enUS": {
        Refresh: "Refresh",
        InformationLevel: "Information Level",
        Period: "Period",
        AsOf: "As of",
        MarketValue: "Market Value",
        Asset: "Asset",
        Purchase: "Purchase",
        Redemption: "Redemption",
        Adjustment: "Adjustment",
        Balance: "Balance",
        Grant: "Grant",
        Grants: "Grants",
        Received: "Received",
        PaidOut: "Paid Out",
        Returned: "Repayment",
        PendingClawBackCol: "Pending<br/>Claw-back",
        PendingClawBack: "Pending Claw-back",
        Transaction: "Transaction",
        Description: "Description",
        TransactionDate: "Trans.Date",
        TransactionNumber: "Trans<br/>Number",
        NotionalTransactionId: "Notional<br/>Trans Id",
        NotionalDetailInformation: "RESP Notional Detail Information",
        NotionalAmount: "Notional<br/>Amount",
        DateRange: "Date Range",
        To: "To",
        ContributionAndIncome: "Contribution & Income",
        AssistedAndUnassisted: "Assisted & Unassisted",
        Activity: "Activity",
        AdjustmentPopupTitle: "RESP Notional Adjustment",
        Reason: "Reason",
        Remarks: "Remarks",
        NotionalAccounts: "Notional Accounts",
        NotionalAccount: "Notional Account",
        BalanceAsOf: "Balance",
        AdjustedBalance: "Adjusted Balance",
        NotionalType: "Notional Type",
        BucketGoingToNegative: "Your action will create a negative Notional balance, please review subsequent transactions in this account.",
        Contribution: "Contribution"	
    },
    "frCA":{
        Refresh: "Rafraîchir",
        InformationLevel: "Niveau d'info",
        Period: "Période",
        AsOf: "Au",
        MarketValue: "Valeur march.",
        Asset: "Actif",
        Purchase: "Achat",
        Redemption: "Rachat",
        Adjustment: "Ajustement",
        Balance: "Solde",
        Grant: "Subvention",
        Grants: "Subventions",
        Received: "Reçu",
        PaidOut: "Versé",
        Returned: "Remboursé",
        PendingClawBackCol: "Récupération<br/>en-cours",
        PendingClawBack: "Récupération<br/>en-cours",
        Transaction: "Transaction",
        Description: "Description",
        TransactionDate: "Date de<br/>trans.",
        TransactionNumber: "Numéro<br/>de trans.",
        NotionalTransactionId: "Id. trans.<br/>théorique",
        NotionalDetailInformation: "Informations théoriques détaillées REEE",
        NotionalAmount: "Montant<br/>théorique",
        DateRange: "Du",
        To: "Au",
        ContributionAndIncome: "Cotisation et revenu",
        AssistedAndUnassisted: "Subventionné et non subventionné",
        Activity: "Activité",
        AdjustmentPopupTitle: "Ajustement notionnelle REEE",
        Reason: "Raison",
        Remarks: "Remarques",
        NotionalAccounts: "Compte notionnel",
        NotionalAccount: "Compte notionnel",
        BalanceAsOf: "Solde",
        AdjustedBalance: "Solde ajusté",
        NotionalType: "Type Notionnel",
        BucketGoingToNegative: "Votre action créera un solde notionnel négatif, veuillez soumettre dans ce compte.",
        Contribution: "Cotisation"
    }
}
