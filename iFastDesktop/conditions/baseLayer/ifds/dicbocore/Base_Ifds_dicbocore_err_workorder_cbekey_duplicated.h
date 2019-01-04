#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicbocore_err_workorder_cbekey_duplicated : public CConditionObject
	{
	public:
		CBase_Ifds_dicbocore_err_workorder_cbekey_duplicated() { }
		~CBase_Ifds_dicbocore_err_workorder_cbekey_duplicated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WORKORDER_CBEKEY_DUPLICATED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  An unknown exception was detected.  An incident report (%INCIDENT_NUMBER%) has been generated.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Une exception inconnue a été détectée. Un rapport d'incident (%INCIDENT_NUMBER%) a été généré.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
	};
}



