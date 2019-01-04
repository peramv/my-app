#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_err_string_exception : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_err_string_exception() { }
		~CIFast_Infrastructure_dicbocore_err_string_exception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STRING_EXCEPTION")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

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



