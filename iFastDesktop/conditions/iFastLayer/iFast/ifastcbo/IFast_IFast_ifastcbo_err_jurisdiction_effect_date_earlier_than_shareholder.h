#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_jurisdiction_effect_date_earlier_than_shareholder : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_jurisdiction_effect_date_earlier_than_shareholder() { }
		~CIFast_IFast_ifastcbo_err_jurisdiction_effect_date_earlier_than_shareholder() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_JURISDICTION_EFFECT_DATE_EARLIER_THAN_SHAREHOLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Jurisdiction date can not be earlier  than shareholder effective date %DATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Jurisdiction date can not be earlier than shareholder effective data %DATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de juridiction ne peut être antérieure à la date d'entrée en vigueur de l'actionnaire du %DATE%.")); }

        // Actions
	};
}



