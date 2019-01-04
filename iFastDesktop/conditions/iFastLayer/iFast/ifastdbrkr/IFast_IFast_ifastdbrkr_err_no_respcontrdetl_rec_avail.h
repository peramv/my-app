#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_respcontrdetl_rec_avail : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_respcontrdetl_rec_avail() { }
		~CIFast_IFast_ifastdbrkr_err_no_respcontrdetl_rec_avail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_RESPCONTRDETL_REC_AVAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No RESPContrDetl record available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein RESPContrDetl-Eintrag verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un registro RESPContrDetl disponible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement des détails de cotisation REEE n'est disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen record RESPContrDetl beschikbaar")); }

        // Actions
	};
}



