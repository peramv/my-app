#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_from_date_future_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_from_date_future_date() { }
		~CIFast_IFast_ifastcbo_err_from_date_future_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FROM_DATE_FUTURE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("From date can not be future dated.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Von-Datum darf nicht in der Zukunft liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de inicio no puede ser en el futuro.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("De la date ne peut être postérieur à la date actuelle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Van-datum kan geen toekomstige datum zijn")); }

        // Actions
	};
}



