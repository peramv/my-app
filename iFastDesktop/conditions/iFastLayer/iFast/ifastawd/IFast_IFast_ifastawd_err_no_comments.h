#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastawd_err_no_comments : public CConditionObject
	{
	public:
		CIFast_IFast_ifastawd_err_no_comments() { }
		~CIFast_IFast_ifastawd_err_no_comments() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_COMMENTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastawd")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Comments have not been entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Comments have not been entered.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les commentaires n'ont pas été saisis.")); }

        // Actions
	};
}



