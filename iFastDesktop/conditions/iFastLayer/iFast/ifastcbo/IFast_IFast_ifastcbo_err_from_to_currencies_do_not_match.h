#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_from_to_currencies_do_not_match : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_from_to_currencies_do_not_match() { }
		~CIFast_IFast_ifastcbo_err_from_to_currencies_do_not_match() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FROM_TO_CURRENCIES_DO_NOT_MATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The from fund currency (%FROM%) and to fund currency (%TO%) do not match")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The from fund currency (%FROM%) and to fund currency (%TO%) do not match")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The from fund currency (%FROM%) and to fund currency (%TO%) do not match")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La monnaie du fonds source (%FROM%) et la monnaie du fonds cible (%TO%) ne correspondent pas.")); }

        // Actions
	};
}



