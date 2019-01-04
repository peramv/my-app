#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_must_have_one_active_rec : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_must_have_one_active_rec() { }
		~CIFast_IFast_ifastdbrkr_err_must_have_one_active_rec() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MUST_HAVE_ONE_ACTIVE_REC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Must have at least 1 active record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es muss mindestens 1 aktiven Eintrag vorhanden sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe tener al menos 1 registro activo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Doit avoir au moins un enregistrement actif.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet ten minste één actief record zijn")); }

        // Actions
	};
}



