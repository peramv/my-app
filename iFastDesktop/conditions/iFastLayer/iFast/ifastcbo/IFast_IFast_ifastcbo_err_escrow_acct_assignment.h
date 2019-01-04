#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_escrow_acct_assignment : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_escrow_acct_assignment() { }
		~CIFast_IFast_ifastcbo_err_escrow_acct_assignment() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ESCROW_ACCT_ASSIGNMENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This account has an Escrow/Assigned assignment.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dieses Konto hat eine Escrow-Zuweisung")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Esta cuenta tiene una cesión de custodia")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a une assignation de mise en garantie au compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit account heeft een pandtoewijzing")); }

        // Actions
	};
}



