#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_recipient_info_not_set_up : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_recipient_info_not_set_up() { }
		~CIFast_IFast_ifastdbrkr_err_recipient_info_not_set_up() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RECIPIENT_INFO_NOT_SET_UP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Recipient Information not set up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Empfänger-Info nicht erstellt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha configurado la información del destinatario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur le bénéficiaire n'est pas réglée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ontvangergegevens zijn niet ingesteld")); }

        // Actions
	};
}



