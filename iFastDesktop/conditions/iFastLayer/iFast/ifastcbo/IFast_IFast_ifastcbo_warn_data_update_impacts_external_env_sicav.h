#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_data_update_impacts_external_env_sicav : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_data_update_impacts_external_env_sicav() { }
		~CIFast_IFast_ifastcbo_warn_data_update_impacts_external_env_sicav() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This investor holds a cross-reference relating to another investment on a database external to iFAST. Ensure account update or deal instruction is also processed, as appropriate, within the alternative database identified by the cross-reference.")); }

        // Actions
	};
}



