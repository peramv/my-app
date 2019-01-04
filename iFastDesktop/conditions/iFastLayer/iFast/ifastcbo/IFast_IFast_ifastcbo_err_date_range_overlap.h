#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_date_range_overlap : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_date_range_overlap() { }
		~CIFast_IFast_ifastcbo_err_date_range_overlap() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DATE_RANGE_OVERLAP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Date range overlapping existing. Please change StartDate or StopDate.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Date range overlapping existing. Please change StartDate or StopDate.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Chevauchement de plages de dates existant. Veuillez changer la date de début ou la date d'arrêt.")); }

        // Actions
	};
}



