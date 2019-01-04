#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_overlapping_or_same_day_commission : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_overlapping_or_same_day_commission() { }
		~CIFast_IFast_ifastdbrkr_err_overlapping_or_same_day_commission() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OVERLAPPING_OR_SAME_DAY_COMMISSION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Can't have overlapping or the same date as previous commissions.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Datum kann sich nicht überschneiden oder mit dem Datum der vorigen Provisionen übereinstimmen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede tener una fecha superpuesta o igual a la de las comisiones anteriores.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il ne peut y avoir de chevauchement avec les commissions précédentes et la date ne peut être la même.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Datums mogen niet hetzelfde zijn als of een overlap vertonen met datums van eerdere commissies")); }

        // Actions
	};
}



