#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_data_request : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_data_request() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_data_request() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_DATA_REQUEST")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  Field %FIELD% cannot have a value for both a list ID and a CBO ID.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  Field %FIELD% cannot have a value for both a list ID and a CBO ID.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sie müssen in beide Felder Zeichenketten eingeben. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  El campo %FIELD% no puede tener un valor para una identificación de lista y una identificación CBO.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Le champ %FIELD% ne peut avoir une valeur pour un code de liste et un code d'optimisation de coûts.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Veld %FIELD% kan geen waarde bevatten voor zowel een lijst-ID als een CBO-ID.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht.")); }
	};
}



