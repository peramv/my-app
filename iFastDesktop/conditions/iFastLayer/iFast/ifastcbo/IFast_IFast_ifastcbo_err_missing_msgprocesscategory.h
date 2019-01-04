#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_missing_msgprocesscategory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_missing_msgprocesscategory() { }
		~CIFast_IFast_ifastcbo_err_missing_msgprocesscategory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MISSING_MSGPROCESSCATEGORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Missing Process Category.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Missing Process Category.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Catégorie de processus manquante")); }

        // Actions
	};
}



