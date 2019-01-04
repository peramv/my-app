#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_course_len_between_1_and_52_weeks : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_course_len_between_1_and_52_weeks() { }
		~CIFast_IFast_ifastcbo_err_course_len_between_1_and_52_weeks() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COURSE_LEN_BETWEEN_1_AND_52_WEEKS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Academic year length should be between 1 and 52 weeks.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La durée de l'année universitaire devrait être entre 1 et 52 semaines.")); }

        // Actions
	};
}



