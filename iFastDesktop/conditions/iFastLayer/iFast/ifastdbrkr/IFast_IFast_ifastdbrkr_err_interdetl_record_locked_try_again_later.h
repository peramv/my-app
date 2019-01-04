#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_interdetl_record_locked_try_again_later : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_interdetl_record_locked_try_again_later() { }
		~CIFast_IFast_ifastdbrkr_err_interdetl_record_locked_try_again_later() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INTERDETL_RECORD_LOCKED_TRY_AGAIN_LATER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Inter-Detl record locked - try again later.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Inter-Detl-Eintrag ist gesperrt, versuchen Sie es später")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de Inter-Detl está bloqueado. Vuelva a intentarlo más tarde.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement des détails de l'intermédiaire est verrouillé – réessayez plus tard.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record Inter-Detl is vergrendeld, probeer het later nog eens")); }

        // Actions
	};
}



