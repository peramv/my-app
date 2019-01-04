#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bpbase_bp_err_field_not_found : public CConditionObject
	{
	public:
		CBase_Ifds_bpbase_bp_err_field_not_found() { }
		~CBase_Ifds_bpbase_bp_err_field_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_FIELD_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  Could not find field for key %KEY%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  Could not find field for key %KEY%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Benutzer ist bereits angemeldet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  No se pudo encontrar el campo  para la clave %KEY%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Champ introuvable pour la clé %KEY%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Veld voor sleutel %KEY% kon niet worden gevonden.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Keine korrigierende Maßnahme erforderlich.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht.")); }
	};
}



