#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_past_cut_off_time : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_past_cut_off_time() { }
		~CIFast_IFast_ifastdbrkr_err_past_cut_off_time() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAST_CUT_OFF_TIME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("It is past cut off time, modification/cancellation not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nach dem Abschluss-Stichtag sind Änderungen/Stornierungen nicht erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Ha pasado el tiempo límite, no se permiten modificaciones/cancelaciones")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'heure limite est passée, la modification/annulation n'est pas autorisée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Na tijdslimiet, wijziging of annulering is niet toegestaan")); }

        // Actions
	};
}



