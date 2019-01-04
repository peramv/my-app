/*********************************************************************************************
 * @file    RESPGrantInfo2.Translation.js
 * @author  Rod Walker
 * @desc    Translation JS file for GrantInfo screen.
 *********************************************************************************************/
/*
 * Histoty:
 *  16 Jul 2014 Aurkarn Mongkonrat P0241773 T81086
 *                    - Redesign the whole screen to be more flexible for the new grants.
 *
 *  21 Jul 2014 Aurkarn Mongkonrat P0241773 T81123
 *                    - Fix issues from T81086
 *
 *	04 Sep 2015 Peeranut L. P0241773 T81342
 *					  - Update French
 *
 *  20 Oct 2015 Aurkarn Mongkonrat P0241773 T81559 DFT0054910
 *					  - Add error messages for SAGES and ADDCESG.
 *
 *  20 Nov 2015 Aurkarn Mongkonrat P0241773 T81771 DFT0055645
 *					  - Separate the redesigned screen to a new program.
 *
 *  21 Dec 2015 Narin Suanlamyai P0241773 T81920 DFT0057786
 *					  - Update translation for grant pop-up title.
 *
 *  28 Dec 2015 Aurkarn Mongkonrat P0241773 T81957 DFT0057748 DFT0057843
 *					  - Add error messages.
 *
 *  16 Mar 2016 Aurkarn Mongkonrat P0241773 T82466 DFT0061077
 *					  - French error message are not displaying correctly on iFast Desktop
 *
 *  11 Apr 2016 Busarakorn S. P0241773 T82726 DFT0061077
 *            - Modified French error message
 *
 */
DesktopWeb.ScreenTranslation = {
    'enUS': {
        SIN: "SIN"
        ,DateOfBirth: "Date Of Birth"
        ,TaxJurisdiction: "Tax Jurisdiction"
        ,TaxType: "Tax Type"
        ,SiblingOnly: "Sibling Only"
        ,SpecimenNum: "Specimen Num"
        ,Address: "Address"
        ,Name: "Name"
        ,SIN_BN: "SIN/BN"
        ,CurrentStatus: "Current Status"
        ,NewStatus: "New Status"
        ,GenerateRT511: "Generate RT511"
        ,CutOffDate: "Cut Off Date"
        ,GrantOption: "Grant Option"
        ,Year: "Year"
        ,StopReason: "Stop Reason"
        ,RESPBeneficiary: "RESP Beneficiary Information"
        ,PrimaryCareGiver_PCG: "Primary Care Giver (PCG)"
        ,CreatedBy: "Created By"
        ,GrantInformation: "Grant Information"
        ,StopDate: "Stop Date"
        ,GrantGridTitle: "Grants"
        ,GrantStatus: "Status"
        ,GrantTypeCol: "Grant"
        ,GrantTypeCMB: "Grant Type"
        ,GrantTypePopup: "Grant"
        ,GrantStatusPopup: "Grant Status"
        ,GrantReaRejRef: "Reason/Reject/Refusal"
        ,EffectiveDate: "Effective Date"
        ,BeneficiaryCMB: "Beneficiary"
        ,AddtionalGrantInfo :"Additional Grant Information"
        ,Retroactive: "Retroactive Additional CESG"
        ,RetroactivePopup: "Retroactive ACESG"
        ,Age: "Age"
        ,GrantYear:"Grant Year"
        ,GrantMaintTitle: "Grant Maintenance"
        ,GrantMaintTitleAdd: "Grant Maintenance - Add"
        ,GrantMaintTitleModify: "Grant Maintenance - Modify"
        ,GrantMaintTitleDelete: "Grant Maintenance - Delete"
        ,RESPBenef: "RESP Beneficiary"
        ,ModDate: "Mod Date"
        ,ProcessDate: "Process Date"
        ,ERR_DEFF_CANNOT_GREATER_THAN_STOPDATE: "Effective Date cannot be greater than stop date."
        ,ERR_STOP_CANNOT_LESS_THAN_EFFDATE: "Stop Date cannot be less than effective date."
        ,ERR_DEFF_CANNOT_FUTUREDATE: "Effective Date cannot be future date."
        ,ERR_REQUIRED_FIELD: "This field is required."
        ,ERR_BCTESG_EFF_DATE_CANNOT_BE_BEFORE: 'BCTESG Application date cannot be before August 15,2015.'
        ,ERR_BCTESG_EFF_DATE_BLANK_NULL_FOR_REQ:
            'BCTESG Application date cannot be blank or null if BCTESG status is "Requested".'
        ,ERR_BCTESG_EFF_DATE_GREATER_THAN_SYSTEM_DATE:'BCTESG Application date cannot be greater than the system date.'
        ,ERR_SAGES_EFF_DATE_GREATER_THAN_SYSTEM_DATE: "SAGES Application date cannot be greater than the system date."
		,ERR_SAGES_EFF_DATE_CANNOT_BE_BEFORE: "SAGES Application date cannot be before the SAGES effective date."
        ,ERR_ADDCESG_EFF_DATE_CANNOT_BE_BEFORE: "ADDCESG Application date cannot be before the ADDCESG effective date."
		,ERR_EFF_AND_STOP_MUST_BE_THE_SAME_YEAR: "Effective date and Stop date must be the same year."
        ,ERR_STOPDATE_CANNOT_LESS_THAN_CURBUSDTE: "Stop Date cannot be less than current business date."
    },
    'frCA':{
        SIN: "NAS"
        ,DateOfBirth: "Date de naissance"
        ,TaxJurisdiction: "Territoire"
        ,TaxType: "Type d'imposition"
        ,SiblingOnly: "Frère/sœur seulement"
        ,SpecimenNum: "No de spécimen"
        ,Address: "Adresse"
        ,Name: "Nom"
        ,SIN_BN: "NAS/NEQ"
        ,CurrentStatus: "Statut actuel"
        ,NewStatus: "Nouv. statut"
        ,GenerateRT511: "Générer RT511"
        ,CutOffDate: "Date de clôture"
        ,GrantOption: "Option de subv."
        ,Year: "Année"
        ,StopReason: "Raison de l’arrêt"
        ,RESPBeneficiary: "Information bénéficiaire REEE"
        ,PrimaryCareGiver_PCG: "Principal fournisseur de soins (PFS)"
        ,CreatedBy: "Créé par"
        ,GrantInformation: "Information de subv."
        ,StopDate: "Date d'arrêt"
        ,GrantGridTitle: "Subventions"
        ,GrantStatus: "Statut"
        ,GrantTypeCol: "Subvention"
        ,GrantTypeCMB: "Type de subv."
        ,GrantTypePopup: "Subvention"
        ,GrantStatusPopup: "Statut de la subvention"
        ,GrantReaRejRef: "Raison/rejet/refus"
        ,EffectiveDate: "Date d'entr. vig."
        ,BeneficiaryCMB: "Bénéficiaire"
        ,AddtionalGrantInfo :"SCEE supplémentaire"
        ,Retroactive: "CEES supplémentaire rétroactive"
        ,RetroactivePopup: "SCEES rétroactive"
        ,Age: "Âge"
        ,GrantYear:"Année de la subvention"
        ,GrantMaintTitle: "Subvention de fonctionnement "
        ,GrantMaintTitleAdd: "Modification/ajout de la subvention"
        ,GrantMaintTitleModify: "Modification/ajout de la subvention"
        ,GrantMaintTitleDelete: "Supprimer de la subvention"
        ,RESPBenef: "Bénéficiaire du REEE"
        ,ModDate: "Modifier la date"
        ,ProcessDate: "Date de traitement"
        ,ERR_DEFF_CANNOT_GREATER_THAN_STOPDATE: "La date d'effet ne peut être postérieure à la date d'arrêt."
        ,ERR_STOP_CANNOT_LESS_THAN_EFFDATE: "La date d'arrêt ne peut pas être antérieure à la date d'effet."
        ,ERR_DEFF_CANNOT_FUTUREDATE: "La date d'effet ne peut être dans le futur."
        ,ERR_REQUIRED_FIELD: "Ce champ est requis"
        ,ERR_BCTESG_EFF_DATE_CANNOT_BE_BEFORE: 
                                            'La date de demande de la SEEEFCB ne peut être antérieure au 15 août 2015.'
        ,ERR_BCTESG_EFF_DATE_BLANK_NULL_FOR_REQ:
            'La date de demande de la SEEEFCB ne peut être vide ou nulle si son statut est « demandé ».'
        ,ERR_BCTESG_EFF_DATE_GREATER_THAN_SYSTEM_DATE:
                                       'La date de demande de la SEEEFCB ne peut être ultérieure à la date du système.'
        ,ERR_SAGES_EFF_DATE_GREATER_THAN_SYSTEM_DATE: 
                                            "La date de demande de la SEEAS ne peut être ultérieure à la date du jour."
		,ERR_SAGES_EFF_DATE_CANNOT_BE_BEFORE: 
                    "La date de demande de la SEEAS ne peut être antérieure à la date d'entrée en vigueur de la SEEAS."
        ,ERR_ADDCESG_EFF_DATE_CANNOT_BE_BEFORE: 
                    "La date de demande de la SCEE supplémentaire ne peut être antérieure à la date d'entrée en \
                     vigueur de la SCEE supplémentaire."
		,ERR_EFF_AND_STOP_MUST_BE_THE_SAME_YEAR: "Entrée en vigueur et la date d'arrêt doivent être de la même année."
        ,ERR_STOPDATE_CANNOT_LESS_THAN_CURBUSDTE: "La date d'arrêt ne peut pas être antérieure à la date jour ouvrable actuel."
    }
}

