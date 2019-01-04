#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_whereuse : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_whereuse() { }
		~CIFast_IFast_ifastcbo_err_duplicate_whereuse() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_Duplicate_WhereUse")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate where used records.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Duplicate where used records.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Copie des enregistrements de contrats associés")); }

        // Actions
	};
}



