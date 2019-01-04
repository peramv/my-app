/*********************************************************************************************
 * @file	RESPGrantInfo.Translation.js
 * @author	
 * @desc	Translation JS file for GrantInfo screen.
 *********************************************************************************************/
 /*
 * Histoty:
 *
 *  30 Apr 2014 G. Thawornwachirakun P0220132 FN03 T55087
 *					- Enhanced for CCS - SAGES RESP Program
 *
 *  23 May 2014 Narin Suanlamyai P0220132 FN03 T55087
 *					- Update error messages
 *
 *  30 May 2014 Narin Suanlamyai P0220132 FN03 DFT0034351 T55198
 *					- Update French
 *
 *  13 Jun 2014 Narin Suanlamyai P0220132 FN03 DFT0034936 T55247
 *					- Update French
 *
 *  10 July 2014 Narin Suanlamyai P0220132 FN03 DFT0036690 T55410
 *					- Add translation for grant information history.
 *
 *  31 July 2014 Narin Suanlamyai P0220132 FN03 DFT0037461 T55508
 *					- Update French translation for StopDate.
 *
 *  18 Aug 2014 Narin Suanlamyai P0220132 FN03 DFT0037754 T55565
 *					- Update French
 *
 *  20 Nov 2015 Aurkarn Mongkonrat P0241773 T81771 DFT0055645
 *					  - Separate the redesigned screen to a new program.
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
		,GrantType_ACES: "Grant Type: ACES"
		,GrantType_QESI: "Grant Type: QESI"
		,RESPBeneficiary: "RESP Beneficiary"
		,PrimaryCareGiver_PCG: "Primary Care Giver (PCG)"
		,AdditionalCESG: "Additional CESG"
		,CanadianLearningBond_CLB: "Canadian Learning Bond (CLB)"
		,CreatedBy: "Created By"
		,GrantInformation: "Grant Information"
		
		//SAGES Section
		,GrantType_SAGES: "SAGES"
		,SAGESRequest: "SAGES Request"
		,SAGESApplicationDate: "SAGES Application Date"
		,FromDate: "From Date"
		,ToDate: "To Date"
		,CancelRequest: "Cancel Request"
		,StopDate: "Stop Date"
		,ERR_APPDATE_CANNOT_GREATER_THAN_SYSDATE: "SAGES Application date cannot be greater than the system date."
		,ERR_APPDATE_CANNOT_LESS_THAN_SAGESDEFF: "SAGES Application date cannot be before the SAGES effective date."
		,ERR_APPDATE_CANNOT_BLANK_FLAG_YES: "SAGES Application date cannot be blank or null if Request SAGES is Yes."
		,ERR_TODATE_CANNOT_LESS_THAN_FROMDATE: "To Date cannot be less than From Date."
		,ERR_DATE_CANNOT_GREATER_THAN_CURDATE: "Date must be equal or less than current business date."
		,NOTI_CANCEL_REQUEST_CONFIRM: "Please validate as any filed SAGES requested from ESDC will be cancelled."
	},
	'frCA':{
		SIN: "NAS"
		,DateOfBirth: "Date de naissance"
		,TaxJurisdiction: "Juridiction fiscale"
		,TaxType: "Type d'imposition"
		,SiblingOnly: "Frère/sœur seulement"
		,SpecimenNum: "No de spécimen"
		,Address: "Adresse"
		,Name: "Nom"
		,SIN_BN: "NAS/NEQ"
		,CurrentStatus: "Statut actuel"
		,NewStatus: "Nouv. statut"
		,GenerateRT511: "Générer RT511"
		,CutOffDate: "Date limite"
		,GrantOption: "Option de subv."
		,Year: "Année"
		,StopReason: "Raison d'arrêt"
		,GrantType_ACES: "Type de subv. : ACES"
		,GrantType_QESI: "Type de subv. : IQEE"
		,RESPBeneficiary: "Bénéficiaire REEE"
		,PrimaryCareGiver_PCG: "Principal responsable"
		,AdditionalCESG: "SCEE supplémentaire"
		,CanadianLearningBond_CLB: "Bon d'études canadien (BEC)"
		,CreatedBy: "Créé par"
		,GrantInformation: "Information de subv."

		//SAGES Section
		,GrantType_SAGES: "Type de subv. : SEEAS"
		,SAGESRequest: "Demande de SEEAS"
		,SAGESApplicationDate: "Date de demande SEEAS"
		,FromDate: "Date de début"
		,ToDate: "Date de fin"
		,CancelRequest: "Demande d'annulation"
		,StopDate: "Date d'arrêt"
		,ERR_APPDATE_CANNOT_GREATER_THAN_SYSDATE: "La date de demande de la SEEAS ne peut être ultérieure à la date du jour."
		,ERR_APPDATE_CANNOT_LESS_THAN_SAGESDEFF: "La date de demande de la SEEAS ne peut être antérieure à la date d'entrée en vigueur de la SEEAS."
		,ERR_APPDATE_CANNOT_BLANK_FLAG_YES: "La date de demande de la SEEAS ne peut être nulle si la demande est à Oui."
		,ERR_TODATE_CANNOT_LESS_THAN_FROMDATE: "La date de fin ne peut pas être antérieure à la date de début."
		,ERR_DATE_CANNOT_GREATER_THAN_CURDATE: "La date doit être ultérieure ou égale à la date du jour."
		,NOTI_CANCEL_REQUEST_CONFIRM: "Veuillez valider car toutes demandes SEEAS déposées au EDSC seront annulées."
	}
}

