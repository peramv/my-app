#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_too_big_min_with_age : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_too_big_min_with_age() { }
		~CIFast_IFast_ifastcbo_err_rif_too_big_min_with_age() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_TOO_BIG_MIN_WITH_AGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Minimum Withdraw Age should be greater or equal to %LEG_MIN_WITH_AGE%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Minimum Withdraw Age should be greater or equal to %LEG_MIN_WITH_AGE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Minimales Abbuch-Alter sollte größer oder gleich %LEG_MIN_WITH_AGE% sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La edad de retiro mínima debe ser superior o igual a %LEG_MIN_WITH_AGE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'âge de retrait minimal devrait être supérieur ou égal à %LEG_MIN_WITH_AGE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Minimumleeftijd voor opname moet groter zijn dan of gelijk aan %LEG_MIN_WITH_AGE%")); }

        // Actions
	};
}



