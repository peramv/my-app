#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_conflicting_record_already_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_conflicting_record_already_exists() { }
		~CIFast_IFast_ifastcbo_err_conflicting_record_already_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONFLICTING_RECORD_ALREADY_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Conflicting record already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Widersprüchlicher Eintrag existiert bereits")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro en conflicto ya existe")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Enregistrement contradictoire déjà existant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Conflicterend record bestaat al")); }

        // Actions
	};
}



