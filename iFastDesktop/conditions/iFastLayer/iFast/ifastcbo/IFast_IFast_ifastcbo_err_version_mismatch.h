#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_version_mismatch : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_version_mismatch() { }
		~CIFast_IFast_ifastcbo_err_version_mismatch() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTCBO_ERR_VERSION_MISMATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("IFast Desktop version %DSK_VER% is not matching data base version %DB_VER%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("IFast Desktop version %DSK_VER% is not matching data base version %DB_VER%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("IFast Desktop version %DSK_VER% is not matching data base version %DB_VER%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("IFast Desktop version %DSK_VER% is not matching data base version %DB_VER%.")); }

		virtual DString GetAction_EN_US() const { return DString(I_("Please use the correct Desktop version.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please use the correct Desktop version.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please use the correct Desktop version.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please use the correct Desktop version.")); }
        // Actions
	};
}



