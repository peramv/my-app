#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sys_fee_invalid_gwb_basedon : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sys_fee_invalid_gwb_basedon() { }
		~CIFast_IFast_ifastcbo_err_sys_fee_invalid_gwb_basedon() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SYS_FEE_INVALID_GWB_BASEDON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid option for the chosen fee.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Option invalide pour les frais sélectionnés")); }

        // Actions
	};
}



