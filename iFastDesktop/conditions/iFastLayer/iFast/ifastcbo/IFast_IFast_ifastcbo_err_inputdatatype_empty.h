#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_inputdatatype_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_inputdatatype_empty() { }
		~CIFast_IFast_ifastcbo_err_inputdatatype_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INPUTDATATYPE_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Input Data Type cannot be blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ du type de données saisies ne peut être laissé vide.")); }

        // Actions
	};
}



