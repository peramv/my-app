#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_actentdeloptn_rec_avail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_actentdeloptn_rec_avail() { }
		~CIFast_IFast_ifastdbrkr_err_no_actentdeloptn_rec_avail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ACTENTDELOPTN_REC_AVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No ActEntDelOptn record available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein ActEntDelOptn-Eintrag verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un registro ActEntDelOptn disponible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement d'option de suppression de l'entité du compte disponible")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen record ActEntDelOptn beschikbaar")); }

        // Actions
	};
}



