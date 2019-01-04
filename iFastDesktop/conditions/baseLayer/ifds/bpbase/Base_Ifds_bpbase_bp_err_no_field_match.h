#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bpbase_bp_err_no_field_match : public CConditionObject
	{
	public:
		CBase_Ifds_bpbase_bp_err_no_field_match() { }
		~CBase_Ifds_bpbase_bp_err_no_field_match() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_NO_FIELD_MATCH")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  No match found for field ID %ID%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  No match found for field ID %ID%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugriff verweigert – Ungültiges Kennwort")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  No se encontró ninguna coincidencia para la identificación de campo %ID%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Aucune correspondance trouvée pour le code de champ %ID%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Er is geen overeenkomst gevonden voor veld-ID %ID%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht.")); }
	};
}



