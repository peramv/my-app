#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_Invalid_institution_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_Invalid_institution_code() { }
		~CIFast_IFast_ifastcbo_err_Invalid_institution_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_INSTITUTION_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid institution code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code d'institution non valable.")); }

        // Actions
	};
}