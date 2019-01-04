/******************************************************************************
 * Procedure: ExternalTA.Translation.js
 * Purpose  : ExternalTA screens manage External Tranfer Agent data
 * Notes    : Open screens by 
 *						 Menu -> System Maintenance -> External TA Fund Linkage
 * History  :
 *		03 Jul 2017 Gomoot T. P0268835 CHG0050132 Order Transmission T85761
 *			- Created
 *
 *		10 Aug 2017 Nopphawan H. P0268835 CHG0050132 DFT0076254 T86004
 *			- Added French translations
 ******************************************************************************/

DesktopWeb.ScreenTranslation = {

	"enUS": {
		ExternalTA: "External TA Fund Linkage"
		,FundGroup: "Fund Group"
		,FundGroupDesc: "Fund Group Description"
		,EmptyText_FundGroup: "Fund Group Code"
		,StartDate: "Start Date"
		,RuleType: "Rule Type"
		,ExtAcct : "External TA Account"
		,RecvNWAddr : "External TA Address"
		,Error_EffectiveDateRequire:"Effective Date must be entered"
		,Error_StartDateNotPriorEndDate: "End Date cannot be prior to Start Date"
		,Error_StartDateOrEndDateIsBlank: "Start Date or End Date must be entered"
		,StopConfirmMsg: "Are you sure you want to delete this record? <br/><br/>The record will set \'Stop Date\' to the next cycle date."
	}

	,'frCA': {
		ExternalTA: "Lien Fonds AT externe"
		,FundGroup: "Groupe de Fonds"
		,FundGroupDesc: "Description du groupe de Fonds"
		,EmptyText_FundGroup: "Code du groupe de Fonds"
		,StartDate: "Date de début"
		,RuleType: "Type de règle"
		,ExtAcct : "Compte AT externe"
		,RecvNWAddr : "Adresse AT externe"
		,StopConfirmMsg: "Souhaitez-vous vraiment effacer cette information? <br/><br/>L'information concernant la « date d'arrêt » sera fixée à la date du prochain cycle."
		,Error_EffectiveDateRequire:"La date effective doit être précisée"
		,Error_StartDateNotPriorEndDate: "La date de fin ne peut être antérieure à la date de début"
		,Error_StartDateOrEndDateIsBlank: "Vous devez préciser les dates de début et de fin"

	}
}