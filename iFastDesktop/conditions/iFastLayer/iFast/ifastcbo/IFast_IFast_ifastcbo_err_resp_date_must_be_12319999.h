#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_resp_date_must_be_12319999 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_resp_date_must_be_12319999() { }
		~CIFast_IFast_ifastcbo_err_resp_date_must_be_12319999() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_DATE_MUST_BE_12319999")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Responsibility Date must be 12/31/9999. Based on the first record, split factor is based on Percentage.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Resp. Date must be 12/31/9999 when total of dilution allocation percentage is 100.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de responsabilité doit être le 31/12/9999. Selon le premier enregistrement, le facteur de partage est basé sur le pourcentage.")); }

        // Actions
	};
}



