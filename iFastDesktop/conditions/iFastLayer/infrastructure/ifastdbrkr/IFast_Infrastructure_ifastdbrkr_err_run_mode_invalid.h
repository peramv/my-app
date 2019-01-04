#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_run_mode_invalid : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_run_mode_invalid() { }
		~CIFast_Infrastructure_ifastdbrkr_err_run_mode_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RUN_MODE_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Output buffer is too small for number. It must be at least %NUMBER% bytes.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Output buffer is too small for number. It must be at least %NUMBER% bytes.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Ausgabepuffer ist zu klein für diese Anzahl. Er muss mindestens %NUMBER% Byte haben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Output buffer is too small for number. It must be at least %NUMBER% bytes.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La mémoire tampon de sortie est trop faible pour la quantité. Elle doit être d'au moins %NUMBER% multiplets.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Output buffer is too small for number. It must be at least %NUMBER% bytes")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Pass in a larger buffer.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Pass in a larger buffer.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Fügen Sie einen größeren Puffer ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Pass in a larger buffer.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Passez à une mémoire-tampon supérieure.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Ga over naar een grotere buffer")); }
	};
}



