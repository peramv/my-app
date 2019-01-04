#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicore_warn_inputdatatype_empty : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicore_warn_inputdatatype_empty() { }
		~CIFast_Infrastructure_dicore_warn_inputdatatype_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INPUTDATATYPE_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Input Data Type cannot be blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ du type de données saisies ne peut être laissé vide.")); }

        // Actions
	};
}



