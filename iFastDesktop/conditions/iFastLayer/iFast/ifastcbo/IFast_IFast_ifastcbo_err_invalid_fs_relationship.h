#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_fs_relationship : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_fs_relationship() { }
		~CIFast_IFast_ifastcbo_err_invalid_fs_relationship() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FS_RELATIONSHIP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This relationship is not applicable for Fund Sponsor.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cette relation n'est pas applicable pour le promoteur de fonds.")); }

        // Actions
	};
}



