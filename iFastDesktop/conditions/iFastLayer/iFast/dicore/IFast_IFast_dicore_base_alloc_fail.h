#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_base_alloc_fail : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_base_alloc_fail() { }
		~CIFast_IFast_dicore_base_alloc_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BASE_ALLOC_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Death notification date entry must be accompanied by an entry in the death date field.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La date de declaration de deces doit être accompagnee d'une entree dans la zone Date de deces.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Todesbenachrichtigungs-Datum muss von einem Eintrag in das Todesdatums-Feld begleitet werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de notificación de fallecimiento debe ir acompañada por una entrada en el campo de fecha de fallecimiento.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La saisie de la date de notification du décès doit être accompagnée d'une saisie dans le champ de la date de décès.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Datum overlijdensbericht moet vergezeld gaan van een invoer in het veld overlijdensdatum")); }

        // Actions
	};
}



