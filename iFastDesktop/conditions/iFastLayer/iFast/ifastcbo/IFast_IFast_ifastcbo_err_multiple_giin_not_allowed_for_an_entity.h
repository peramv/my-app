#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_multiple_giin_not_allowed_for_an_entity : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_multiple_giin_not_allowed_for_an_entity() { }
		~CIFast_IFast_ifastcbo_err_multiple_giin_not_allowed_for_an_entity() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_GIIN_NOT_ALLOWED_FOR_AN_ENTITY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicated GIIN Setup.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mise en œuvre du GIIN dupliquée.")); }

        // Actions
	};
}



