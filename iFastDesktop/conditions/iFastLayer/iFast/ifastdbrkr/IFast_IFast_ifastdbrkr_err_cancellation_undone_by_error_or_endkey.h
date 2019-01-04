#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cancellation_undone_by_error_or_endkey : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cancellation_undone_by_error_or_endkey() { }
		~CIFast_IFast_ifastdbrkr_err_cancellation_undone_by_error_or_endkey() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANCELLATION_UNDONE_BY_ERROR_OR_ENDKEY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cancellation was undone by an ERROR or an ENDKEY action.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'annulation a été annulée par une ERREUR ou une action avec la touche FIN.")); }

        // Actions
	};
}



