#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_type_for_family_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_type_for_family_code() { }
		~CIFast_IFast_ifastcbo_err_duplicate_type_for_family_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_TYPE_FOR_FAMILY_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Type already exists for the shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Type already exists for the shareholder.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Type already exists for the shareholder.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type existe déjà pour l'actionnaire.")); }

        // Actions
	};
}



