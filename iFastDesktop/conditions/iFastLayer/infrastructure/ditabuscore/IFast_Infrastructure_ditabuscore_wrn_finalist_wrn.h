#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ditabuscore_wrn_finalist_wrn : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ditabuscore_wrn_finalist_wrn() { }
		~CIFast_Infrastructure_ditabuscore_wrn_finalist_wrn() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WRN_FINALIST_WRN")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("^'")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("^'")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("^'")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("^'")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("^'")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("^'")); }

        // Actions
	};
}



