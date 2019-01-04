#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_academic_day_must_be_01 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_academic_day_must_be_01() { }
		~CIFast_IFast_ifastcbo_err_academic_day_must_be_01() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACADEMIC_DAY_MUST_BE_01")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Academic start day must be '01'.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le jour de début de l'enseignement doit être 01.")); }

        // Actions
	};
}



