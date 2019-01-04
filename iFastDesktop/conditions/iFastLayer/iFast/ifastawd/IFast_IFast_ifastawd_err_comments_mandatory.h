#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastawd_err_comments_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastawd_err_comments_mandatory() { }
		~CIFast_IFast_ifastawd_err_comments_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COMMENTS_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastawd")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Comments are mandatory.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Comments are mandatory.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les commentaires sont obligatoires.")); }

        // Actions
	};
}



