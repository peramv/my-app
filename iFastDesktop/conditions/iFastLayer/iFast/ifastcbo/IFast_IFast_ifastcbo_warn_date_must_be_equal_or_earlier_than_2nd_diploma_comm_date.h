#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_date_must_be_equal_or_earlier_than_2nd_diploma_comm_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_date_must_be_equal_or_earlier_than_2nd_diploma_comm_date() { }
		~CIFast_IFast_ifastcbo_warn_date_must_be_equal_or_earlier_than_2nd_diploma_comm_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DATE_MUST_BE_EQUAL_OR_EARLIER_THAN_2ND_DIPLOMA_COMM_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The date must be equal or earlier than end of the second month of the original Diploma commitment date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date doit se situer avant ou être équivalente à la fin du deuxième mois de l'engagement PAC d'origine.")); }

        // Actions
	};
}



