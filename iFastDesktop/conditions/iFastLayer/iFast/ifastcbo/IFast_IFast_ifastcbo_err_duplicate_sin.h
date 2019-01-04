#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_sin : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_sin() { }
		~CIFast_IFast_ifastcbo_err_duplicate_sin() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_SIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("SIN already exists in the system.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("SIN bereits im System vorhanden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("SIN ya existe en el sistema.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le NAS existe déjà dans le système.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("SIN bestaat al in het systeem")); }

        // Actions
	};
}



