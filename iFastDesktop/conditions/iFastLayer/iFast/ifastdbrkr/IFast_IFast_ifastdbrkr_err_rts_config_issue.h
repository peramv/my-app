#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_rts_config_issue : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_rts_config_issue() { }
		~CIFast_IFast_ifastdbrkr_err_rts_config_issue() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RTS_CONFIG_ISSUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is a configuration issue with iFast Desktop. Please contact the service desk.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème de configuration avec le bureau iFAST. Veuillez communiquer avec le centre de services.")); }

        // Actions
	};
}



