#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_annuitant_date_of_birth_is_changing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_annuitant_date_of_birth_is_changing() { }
		~CIFast_IFast_ifastcbo_err_annuitant_date_of_birth_is_changing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ANNUITANT_DOFBIRTH_IS_CHANGING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_( "Date of Birth is changing. Financial Trade adjustments and LOI may be required." )); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Changement de la date de naissance. Des ajustements aux transactions financières et LI peuvent être exigés.")); }
		
        // Actions
	};
}


