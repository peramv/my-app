#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_oldest_legal_date_cannot_be_in_the_past : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_oldest_legal_date_cannot_be_in_the_past() { }
		~CIFast_IFast_ifastcbo_err_oldest_legal_date_cannot_be_in_the_past() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OLDEST_LEGAL_DATE_CANNOT_BE_IN_THE_PAST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Oldest legal date cannot be in the past.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ältestes Geschäftsdatum darf nicht in der Vergangenheit liegen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha legal más antigua no puede ser anterior.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La plus ancienne date légale ne peut être antérieure à la date actuelle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Oudste wettelijke datum kan niet in het verleden liggen")); }

        // Actions
	};
}



