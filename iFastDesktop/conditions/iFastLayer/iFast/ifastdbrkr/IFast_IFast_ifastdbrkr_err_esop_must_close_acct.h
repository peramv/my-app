#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_esop_must_close_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_esop_must_close_acct() { }
		~CIFast_IFast_ifastdbrkr_err_esop_must_close_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ESOP_MUST_CLOSE_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("ESoP Transfer must close the Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("EsoP-Transfer muss Konto schließen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La transferencia ESoP debe cerrar la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert RADE doit fermer le compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("ESoP-overdracht moet het account afsluiten")); }

        // Actions
	};
}



