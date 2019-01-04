#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sin_dupliate_with_other_account_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sin_dupliate_with_other_account_entity() { }
		~CIFast_IFast_ifastcbo_err_sin_dupliate_with_other_account_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SIN_DUPLIATE_WITH_OTHER_ACCOUNT_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("SIN is already used by other account entity(%ENTITY_TYPE%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le NAS est déjà utilisé par une autre entité de compte (%ENTITY_TYPE%).")); }

        // Actions
	};
}



