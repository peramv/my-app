#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_bad_link_to_crtstack : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_bad_link_to_crtstack() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_bad_link_to_crtstack() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_BAD_LINK_TO_CRTSTACK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Distribution record not available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Distribution record not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verteilungseintrag nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de distribución no está disponible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de distribution n'est pas disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Distributierecord is niet beschikbaar")); }

        // Actions
	};
}



