#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bpbase_bp_err_must_run_modeless : public CConditionObject
	{
	public:
		CBase_Infrastructure_bpbase_bp_err_must_run_modeless() { }
		~CBase_Infrastructure_bpbase_bp_err_must_run_modeless() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_MUST_RUN_MODELESS")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this request count.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this request count.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese Anfragezahl nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este recuento de solicitudes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce dénombrement de demande.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent deze telopdracht niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



