/*********************************************************************************************
 * @file	DesktopWeb.Translation.js
 * @author 	Rod Walker 
 * @desc	Contains translation lookup methods and common translations used across screens.
 *********************************************************************************************/
/*
 * Procedure: DesktopWeb.Translation.js
 *
 * Purpose  : Main Translation Object and common translations
 *             
 * Notes    : 
 *
 * History  :  
 *		22 May 2014 N. Suanlamyai P0225140 T55105
 *					- Add broker, branch, sales rep translations to common
 *		19 May 2016 Lalitphan S.  P0241773 T82876
 *					- Add cookie disable translation
 *
 */

DesktopWeb.Translation = {
	locale: (!DesktopWeb._SCREEN_PARAM_MAP['locale'] ? 'enUS' : DesktopWeb._SCREEN_PARAM_MAP['locale']) 
	
	,getTranslation: function(key)
	{
		var str = DesktopWeb.Translation.getCommonTranslationMap()[key];
		if (!str)
		{
			str = DesktopWeb.Translation.getScreenTranslationMap()[key];
		}		
		return str;					
	}
	
	,getScreenTranslationMap: function()
	{		
		if (DesktopWeb.ScreenTranslation[this.locale])
		{	
			return DesktopWeb.ScreenTranslation[this.locale];
		}
		else
		{
			throw new Error("No translation found for specified language (" + this.locale + ")");
		}
	}
	
	,getCommonTranslationMap: function()
	{
		if (this.common[this.locale])
		{		
			return this.common[this.locale];
		}
		else
		{
			throw new Error("No translation found for specified language (" + this.locale + ")");
		}
	}
	
	,getTranslationMap: function()
	{		
		return Ext.apply({}, this.getScreenTranslationMap(), this.getCommonTranslationMap()) 
	}
	
	,common: {
		'enUS': {
			Broker: "Broker"
			,Branch: "Branch"
			,SalesRep: "Sales Rep"
			,Error: "Error"
			,Warning: "Warning"
			,Information: "Information"
			,Yes: "Yes"
			,No: "No"								
			,Next: "Next"
			,Previous: "Previous"
			,More: "More"
			,Close: "Close"
			,Add: "Add"
			,Modify: "Modify"
			,Delete: "Delete"
			,OK: "OK"
			,Cancel: "Cancel"
			,DeleteConfirmMsg: "Are you sure you want to delete this record?"
			,Up: "Up"
			,Down: "Down"
			,Remove: "Remove"
			,Available: "Available"
			,Selected: "Selected"
			,User: "User"
			,Field: "Field"
			,Date: "Date"
			,Time: "Time"
			,PreviousValue: "Previous Value"
			,NewValue: "New Value"
			,ServiceCallFailed: "Service Call Failed"
			,Service: "Service"
			,Environment: "Environment"
			,Historical: "Historical"
			,DiscardQuestion: "You have unfinished updates - Do you want to discard them?"
			,DiscardWarning: "If you choose to Discard, all changes since your last confirmation will be wiped out. This action cannot be undone!"
			,Loading: "Loading"
			,ProcMsg_Loading: "Loading ..."							
			,Saving: "Saving"
			,ProcMsg_Saving: "Saving ..."
			,Validating: "Validating"			
			,ProcMsg_Validating: "Validating ..."
			,Processing: "Processing"
			,ProcMsg_Processing: "Processing ..."
			,ProcMsg_Searching: "Searching ..."
			,Account: "Account"
			,Beneficiary: "Beneficiary"
			,FldRequired: "This field is required"
			,Search: "Search"
			,Amount: "Amount"
			,Status: "Status"
			,Value: "Value"
			,Year: "Year"			
			,Admin: "Admin"
			,EffectiveDate: "Effective Date"
			,StopDate: "Stop Date"
			,Username: "Username"
			,ModUser: "Mod. User"
			,ProcessDate: "Process Date"
			,ModDate: "Mod. Date"
			,History: "History"
			,Edit: "Edit"
			,Code: "Code"
			,PercentRequired: "Value must be between 0 and 100"
			,Level: "Level"
			,Rate: "Rate"
			,Lower: "Lower"
			,Upper: "Upper"
			,FromDate: "From Date"
			,ToDate: "To Date"
			,Term: "Term"
			,SearchBy: "Search By"
			,Fund: "Fund"
			,Class: "Class"
			,Reset: "Reset"
			,EffDate: "Eff. Date"
			,All: "All"
			,Save: "Save"
			,New: "New"
			,Summary: "Summary"
			,CookieDisable: "Cookies are blocked by your browser. Please enable cookies, as the application requires it."
		}
		,'frCA': {
			Broker: "Courtier"
			,Branch: "Agence"
			,SalesRep: "Représentant"
			,Error: "Erreur"
			,Warning: "Avertissement"
			,Information: "Information"
			,Yes: "Oui"
			,No: "Non"								
			,Next: "Suivant"
			,Previous: "Précédent"
			,More: "Plus"
			,Close: "Fermer"
			,Add: "Ajouter"
			,Modify: "Modifier"
			,Delete: "Supprimer"
			,OK: "Ok"
			,Cancel: "Annuler"
			,DeleteConfirmMsg: "Êtes-vous sûr de vouloir supprimer cet enregistrement?"
			,Up: "Haut"
			,Down: "Bas"
			,Remove: "Enlever"
			,Available: "Disponible"
			,Selected: "Sélectionné"
			,User: "Utilisateur"
			,Field: "Champ"
			,Date: "Date"
			,Time: "Heure"
			,PreviousValue: "Valeur précédente"
			,NewValue: "Nouvelle valeur"
			,ServiceCallFailed: "Échec de l'appel de service"
			,Service: "Service"
			,Environment: "Environnement"
			,Historical: "Historique"
			,DiscardQuestion: "Certaines mises à jour ne sont pas terminées. Voulez-vous les supprimer?"
			,DiscardWarning: "Si vous choissisez de supprimer, tous les changements effectués depuis votre dernière confirmation seront effacés. Cette action ne peut être annulée!"
			,Loading: "Téléchargement en cours"
			,ProcMsg_Loading: "Téléchargement en cours ..."							
			,Saving: "Enregistrement en cours"
			,ProcMsg_Saving: "Enregistrement en cours ..."
			,Validating: "Validation en cours"			
			,ProcMsg_Validating: "Validation en cours ..."
			,Processing: "Traitement en cours"
			,ProcMsg_Processing: "Traitement en cours ..."
			,ProcMsg_Searching: "Searching ..."
			,Account: "Compte"
			,Beneficiary: "Bénéficiaire"
			,FldRequired: "Ce champ doit être rempli."
			,Search: "Recherche"
			,Amount: "Montant"
			,Status: "Statut"
			,Value: "Valeur"
			,Year: "Année"			
			,Admin: "Administration"
			,EffectiveDate: "Date d'entrée en vigueur"
			,StopDate: "Date d'arrêt"
			,Username: "Nom d'utilisateur"
			,ModUser: "Modifier l'utilisateur"
			,ProcessDate: "Date de traitement"
			,ModDate: "Modifier la date"
			,History: "Historique"
			,Edit: "Édition"
			,Code: "Code"
			,PercentRequired: "La valeur doit être située entre 0 et 100."
			,Level: "Niveau"
			,Rate: "Taux"
			,Lower: "Inférieur"
			,Upper: "Supérieur"
			,FromDate: "De la date"
			,ToDate: "Vers la date"
			,Term: "Terme"
			,SearchBy: "Recherche par"
			,Fund: "Fonds"
			,Class: "Classe"
			,Reset: "Revaloriser"
			,EffDate: "Date d'entrée en vigueur"
			,All: "Tout"
			,Save: "Enregistrer"
			,New: "Nouveau"
			,Summary: "Sommaire"
			,CookieDisable: "Cookies are blocked by your browser. Please enable cookies, as the application requires it."
		}
	}
}




