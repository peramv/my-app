#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_missing_aggrordnum : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_missing_aggrordnum() { }
		~CIFast_IFast_ifastcbo_err_missing_aggrordnum() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MISSING_AGGRORDNUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Missing Aggregate Order Number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Missing Aggregate Order Number.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro d'ordre global manquant")); }

        // Actions
	};
}



