#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_one_fs_where_use : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_one_fs_where_use() { }
		~CIFast_IFast_ifastcbo_err_one_fs_where_use() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONE_FS_WHERE_USE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one Fund Sponsor record is allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul enregistrement de promoteur de fonds est autorisé.")); }

        // Actions
	};
}



