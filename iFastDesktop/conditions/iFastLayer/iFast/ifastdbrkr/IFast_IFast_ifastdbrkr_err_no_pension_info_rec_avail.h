#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_pension_info_rec_avail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_pension_info_rec_avail() { }
		~CIFast_IFast_ifastdbrkr_err_no_pension_info_rec_avail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_PENSION_INFO_REC_AVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Pension Information record available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein Renteninformationseintrag verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un registro de información de jubilación disponible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement d'information sur le fonds de pension n'est disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen record voor pensioengegevens beschikbaar")); }

        // Actions
	};
}



