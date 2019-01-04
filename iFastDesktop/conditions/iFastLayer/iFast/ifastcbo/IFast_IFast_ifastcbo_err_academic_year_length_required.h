#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_academic_year_length_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_academic_year_length_required() { }
		~CIFast_IFast_ifastcbo_err_academic_year_length_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACADEMIC_YEAR_LENGTH_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Academic year length is required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La durée de l'année universitaire est requise.")); }

        // Actions
	};
}



