#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_resp_date_must_be_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_resp_date_must_be_entered() { }
		~CIFast_IFast_ifastcbo_err_resp_date_must_be_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RESP_DATE_MUST_BE_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Resp. Date Must be entered when total of dilution allocation percentage is 0.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Resp. Date Must be entered when total of dilution allocation percentage is 0.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de responsabilité doit être saisie lorsque le total du pourcentage de répartition de la dilution est de zéro.")); }

        // Actions
	};
}



