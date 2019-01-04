#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cannot_restart_capped_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cannot_restart_capped_fund() { }
		~CIFast_IFast_ifastcbo_err_cannot_restart_capped_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_RESTART_CAPPED_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User does not have permission to restart a capped fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("User does not have permission to restart a capped fund.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("User does not have permission to restart a capped fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur n'est pas autorisé à redémarrer un fonds plafonné.")); }

        // Actions
	};
}



