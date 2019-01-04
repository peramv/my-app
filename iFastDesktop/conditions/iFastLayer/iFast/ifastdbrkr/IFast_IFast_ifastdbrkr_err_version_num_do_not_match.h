#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_version_num_do_not_match : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_version_num_do_not_match() { }
		~CIFast_IFast_ifastdbrkr_err_version_num_do_not_match() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VERSION_NUM_DO_NOT_MATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Version numbers do not match.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Version numbers do not match.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Version numbers do not match.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les numéros de version ne correspondent pas.")); }

        // Actions
	};
}



