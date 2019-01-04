#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bpbase_bp_err_id_out_of_range_for_field : public CConditionObject
	{
	public:
		CBase_Ifds_bpbase_bp_err_id_out_of_range_for_field() { }
		~CBase_Ifds_bpbase_bp_err_id_out_of_range_for_field() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_ID_OUT_OF_RANGE_FOR_FIELD")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  ID %ID% is out of range for field %FIELD%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  ID %ID% is out of range for field %FIELD%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Benutzer muss sich erst anmelden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  La identificación %ID%  está fuera de rango para el campo %FIELD%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Le code %ID% est hors plage pour le champ %FIELD%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  ID %ID% ligt buiten het bereik voor veld %FIELD%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Melden Sie sich an und versuchen Sie, diesen Schritt erneut auszuführen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht.")); }
	};
}



