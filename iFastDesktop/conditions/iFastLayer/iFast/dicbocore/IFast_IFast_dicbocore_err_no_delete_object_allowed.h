#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_no_delete_object_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_no_delete_object_allowed() { }
		~CIFast_IFast_dicbocore_err_no_delete_object_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_DELETE_OBJECT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one %CODE% address code may be created for this entity. Please enter another code, or delete the %CODE% address and then create the new address.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Un seul code d'adresse %CODE% peut être cree pour cette entite. Veuillez saisir un autre code ou supprimer l'adresse %CODE% puis creer la nouvelle adresse.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur eine  %CODE%-Adresse kann für dieses Objekt erstellt werden. Bitte geben Sie einen anderen Code ein oder löschen Sie die  %CODE%-Adresse und erstellen Sie eine neue.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo puede crearse un código de dirección %CODE% para esta entidad. Por favor asigne otro código o elimine la dirección %CODE% y luego cree la nueva dirección.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul code d'adresse %CODE% peut être créé pour cette entité. Veuillez saisir un autre code, ou supprimer cette adresse %CODE% et ensuite créer la nouvelle adresse.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er kan slechts één %CODE% adrescode worden gemaakt voor deze eenheid. Geef een andere code op of wis het %CODE% adres en maak vervolgens een nieuw adres")); }

        // Actions
	};
}



