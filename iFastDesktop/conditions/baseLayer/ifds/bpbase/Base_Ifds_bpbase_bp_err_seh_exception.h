#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bpbase_bp_err_seh_exception : public CConditionObject
	{
	public:
		CBase_Ifds_bpbase_bp_err_seh_exception() { }
		~CBase_Ifds_bpbase_bp_err_seh_exception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_SEH_EXCEPTION")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bpbase")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  An unknown exception was detected.  An incident report (%INCIDENT_NUMBER%) has been generated.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Une exception inconnue a été détectée. Un rapport d'incident (%INCIDENT_NUMBER%) a été généré.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
	};
}



